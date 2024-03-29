# import the necessary modules
import socket
from threading import Thread, Lock

lock = Lock ()          # to regulate the limit on number of active threads at a time

activeThreadCount = 0           # number of threads currently active
MAXIMUM_PROCESSING = 3          # maximum number of clients that can be served simultaneously
MAXIMUM_WAITING = 2             # maximum number of clients waiting to connect to server

# specify a host network interface, here we use loopback interface whose IPv4 address is 127.0.0.1
# If a hostname is used in the host portion of IPv4/v6 socket address, the program may show a
# non-deterministic behavior, as Python uses the first address returned from the DNS resolution
HOST = '127.0.0.1' 

# reserve a port on local machine for listening to incoming client requests
PORT = 12345


# new thread for a new connection
class ConnectionThread (Thread) :
    def __init__ (self, clientAddress, clientSocket) -> None :
        Thread.__init__ (self)
        
        # increment the active thread count
        # lock must be acquired to prevent possible race conditions
        lock.acquire ()
        global activeThreadCount
        activeThreadCount += 1
        lock.release ()

        # save the properties of the incoming client communication
        self.csocket = clientSocket
        self.caddr = clientAddress
        print ('Got new connection from', clientAddress)

    # override the __init__ method to specify the code that the thread would run on
    def run (self) -> None:

        # send a message to indicate that the server is ready to respond
        self.csocket.send(bytes("You are now connected to server.\n\tSay something and I'll echo the message.\n\tSay bye to terminate the session.",'utf-8'))
        while True:
            try:
                msg = self.csocket.recv (1024)         # a blocking call to receive message from client in bytes form
            except:
                print ('Cannot receive data')           # in case the client is abrubtly terminated
            
            if not msg:            # if the message contains no data, it must be due to some error
                break

            msg = msg.decode ()         # decode the message to string format to interpret
            if msg == 'bye' :           # if msg is 'bye', the client wants to disconnect
                break
            
            print ('From client at', self.caddr[1], 'received: ', msg)

            # echo the message sent by client, back to client
            self.csocket.sendall (bytes(msg, 'UTF-8'))

        # message to show that the client has disconnected
        print ("Client at ", self.caddr , " disconnected...")
        
        # close the socket used for connecting to the client at the specific address
        self.csocket.close ()
        
        # decrement the active thread count
        lock.acquire ()
        global activeThreadCount
        activeThreadCount -= 1
        lock.release ()		

# create a socket object which supports context manager types
# this is used to listen to incoming client connection requests
# AF_INET refers to the address family ipv4. 
# The SOCK_STREAM means connection oriented TCP protocol.
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:			

    print("Server started")

    # set socket options, SO_REUSEADDR specifies that the local 
    # address to which the socket binds can be reused
    server.setsockopt (socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    # Next bind to the port
    server.bind((HOST, PORT))		
    print ("Server socket binded to %s" %(PORT))

    # put the socket into listening mode, Its backlog parameter 
    # specifies the number of unaccepted connections that the 
    # system will allow before refusing new connections.
    server.listen (MAXIMUM_WAITING)	
    print ("Server is waiting for client request...")	

    # a forever loop until we interrupt it or an error occurs
    while True:

        # fetch the active thread count
        # lock ensures fetch does not take place while
        # the value is being updated
        lock.acquire ()
        n = activeThreadCount
        lock.release ()

        if n < MAXIMUM_PROCESSING:
            # Establish connection with client
            # a new socket is returned for connecting to the client
            # which is different from the listening socket
            conn, addr = server.accept()
            
            # interaction with client continues in a new thread
            newthread = ConnectionThread (addr, conn)
            newthread.start ()