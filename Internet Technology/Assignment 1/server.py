import socket
from threading import Thread, Lock
from user import User

# to regulate the limit on number of active threads at a time
lock = Lock()

activeThreadCount = 0           # number of threads currently active
# maximum number of clients that can be served simultaneously
MAXIMUM_PROCESSING = 3
MAXIMUM_WAITING = 2             # maximum number of clients waiting to connect to server

# specify a host network interface, here we use loopback interface whose IPv4 address is 127.0.0.1
# If a hostname is used in the host portion of IPv4/v6 socket address, the program may show a
# non-deterministic behavior, as Python uses the first address returned from the DNS resolution
HOST = '127.0.0.1'

# reserve a port on local machine for listening to incoming client requests
PORT = 12345

# dictionary of users
users = {}


class ConnectionThread (Thread):
    """new thread for a new connection"""

    def __init__(self, clientAddress, clientSocket) -> None:
        Thread.__init__(self)

        # increment the active thread count
        # lock must be acquired to prevent possible race conditions
        lock.acquire()
        global activeThreadCount
        activeThreadCount += 1
        lock.release()

        # save the properties of the incoming client communication
        self.csocket = clientSocket
        self.caddr = clientAddress

        clientUserName = self.csocket.recv(1024).decode()
        self.csocket.sendall(bytes("ok", "UTF-8"))

        if clientUserName not in users:
            self.user = User(clientUserName)
            users[clientUserName] = self.user
        else:
            self.user = users[clientUserName]

        print('Got new connection from', clientAddress)

    # override the __init__ method to specify the code that the thread would run on
    def run(self) -> None:
        try:
            while True:
                # a blocking call to receive message from client in bytes form
                msg = self.csocket.recv(1024)

                if not msg:                # if the message contains no data, it must be due to some error
                    break

                msg = msg.decode()         # decode the message to string format to interpret

                print('From client at', self.caddr[1], 'received:', msg)

                query = msg.split(" ")
                if query[0] == "get":
                    self.csocket.send(
                        bytes(self.user.getValue(query[1]), 'utf-8'))
                elif query[0] == "put":
                    self.user.setValue(query[1], query[2])
                    self.csocket.send(bytes("$", 'utf-8'))

                elif query[0] == "viewall":
                    password = query[1]
                    msg = ""
                    i = 1
                    permissionStatus = self.user.upgrade(password)
                    if permissionStatus is True:
                        for user in users.values():
                            msg += "\nUser " + str(i) + " -->"
                            msg += str(user)
                            msg += "\n"
                            i += 1
                    else:
                        msg = "Access denied"

                    self.csocket.send(bytes(msg, 'utf-8'))

        except Exception as ex:
            print(ex)

        finally:
            # message to show that the client has disconnected
            print("Client at", self.caddr, "disconnected...")

            # close the socket used for connecting to the client at the specific address
            self.csocket.close()

            # decrement the active thread count
            lock.acquire()
            global activeThreadCount
            activeThreadCount -= 1
            lock.release()


# create a socket object which supports context manager types
# this is used to listen to incoming client connection requests
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:

    print("Server started")

    # set socket options, SO_REUSEADDR specifies that the local
    # address to which the socket binds can be reused
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    # Next bind to the port
    server.bind((HOST, PORT))
    print("Server socket bound to host: %s port: %s" % (HOST, PORT))

    # put the socket into listening mode, Its backlog parameter
    # specifies the number of unaccepted connections that the
    # system will allow before refusing new connections.
    server.listen(MAXIMUM_WAITING)
    print("Server is waiting for client request...")

    # a forever loop until we interrupt it or an error occurs
    while True:
        try:
            # fetch the active thread count
            # lock ensures fetch does not take place while
            # the value is being updated
            lock.acquire()
            n = activeThreadCount
            lock.release()

            if n < MAXIMUM_PROCESSING:
                # Establish connection with client
                # a new socket is returned for connecting to the client
                # which is different from the listening socket
                conn, addr = server.accept()

                # interaction with client continues in a new thread
                newthread = ConnectionThread(addr, conn)
                newthread.start()
        except:
            break

print("Server ended")
