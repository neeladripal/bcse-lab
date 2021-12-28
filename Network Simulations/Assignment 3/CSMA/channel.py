import socket
from threading import Thread, Lock
import errorInjection as ei
import random
import time

BUSY_STATUS="idle"
VULNERABLE_TIME=0.15
ENERGY=0
ENERGY_LEVEL=50

# dictionary to store each connection information i.e. - ' name : [self socket, self address, receiver name] '
clients={}
# define the lock object
lock=Lock()
settingsLock=Lock()

def process_packet(packet:str):
    """Function to select if original packet or tainted packet or no packet will be sent"""
    # randomly generate what would be done
    flag=random.randint(0,100)

    if(flag>=0 and flag<85):
        return packet
    elif(flag>=85 and flag<90):
        return ei.injectError(packet)
    elif(flag>=90 and flag<95):
        time.sleep(0.5)
        return packet
    else:
        return ''

class ConnectionThread (Thread) :
    def __init__ (self, clientSocket, clientAddress) -> None :
        Thread.__init__ (self)

        # save the properties of the incoming client communication
        self.csocket = clientSocket
        self.caddr = clientAddress
        self.cname = None
        print ('\nGot new connection from', clientAddress)

    def setConnection (self):
        """Function to establish a new connection"""
        senderId = self.cname.split('#')[1]
        rname = "receiver#" + str(senderId)

        settingsLock.acquire()
        rsocket = clients[rname][0]
        raddr = clients[rname][1]
        clients[rname][2] = self.cname
        clients[rname][3] = 384
        clients[self.cname][2] = rname
        clients[self.cname][3] = 576
        settingsLock.release()

        self.csocket.send (str.encode('$'.join([rname, str(raddr[1])])))
        rsocket.send (str.encode('$'.join([self.cname, str(self.caddr[1])])))

    def revokeConnection (self) -> None:
        """Function to revoke an established connection"""
        settingsLock.acquire()
        rname = clients[self.cname][2]
        clients[rname][2] = None
        clients[self.cname][2] = None
        clients[rname][3] = clients[self.cname][3] = 1024
        settingsLock.release()
        
        self.csocket.send(str.encode("Sending completed"))
        
        # Print end of data transfer
        print(self.cname,'ended transferring data to',rname)
        

    # override the run method to specify the code that the thread would run on
    def run (self) -> None:
        # send a message to indicate that the server is ready to respond
        self.csocket.send(bytes("You are now connected to server.",'utf-8'))

        # receive client name from client
        self.cname=self.csocket.recv(1024).decode()
        
        # send client address (port number) to the client
        self.csocket.send(bytes(str(self.caddr[1]), 'UTF-8'))

        # update clients with the new client
        lock.acquire()
        clients[self.cname]=[self.csocket,self.caddr,None,1024]
        lock.release()
        
        data = "open"

        global BUSY_STATUS
        global VULNERABLE_TIME
        global ENERGY
        global ENERGY_LEVEL

        while data!="close":
            inputBuffer = clients[self.cname][3]
            data = self.csocket.recv(inputBuffer).decode()

            if (clients[self.cname][2] == None):
                if data == "request for sending":
                    self.setConnection()
            
            else:
                rsocket = clients[clients[self.cname][2]][0]
                if data == "start":
                    rsocket.send(str.encode(data))
                elif data == "end":
                    rsocket.send(str.encode(data))
                    self.revokeConnection()
                else:
                    lock.acquire()
                    BUSY_STATUS="busy"
                    ENERGY = ENERGY + ENERGY_LEVEL
                    lock.release()

                    newData = process_packet(data)
                    
                    okSend = True
                    now=time.time()
                    while (time.time() - now < VULNERABLE_TIME) and (okSend == True):
                        if ENERGY >= 100:
                            self.csocket.send(str.encode("collision"))
                            okSend = False
                
                    if(newData != '' and okSend == True):
                        rsocket.send(str.encode(newData))

                    lock.acquire()
                    BUSY_STATUS="idle"
                    ENERGY = ENERGY - ENERGY_LEVEL
                    lock.release()

        # close the connection
        self.csocket.close()

        # message to show that the client has been disconnected
        print ("Client at", self.caddr, "disconnected")

        # remove map entries
        lock.acquire()
        clients.pop(self.cname)
        lock.release()

class MonitorThread (Thread):
    def __init__ (self, clientSocket, clientAddress) -> None :
        Thread.__init__ (self)

        # save the properties of the incoming client communication
        self.csocket = clientSocket
        self.caddr = clientAddress

        print ('\nGot new monitor connection from', clientAddress)

    def run (self):
        global BUSY_STATUS
        received = "open"
        while (received != "close"):
            received = self.csocket.recv(1024).decode()
            if received == "status?":
                self.csocket.send (str.encode(BUSY_STATUS))

        self.csocket.close()
        print ("Monitor at", self.caddr, "disconnected")


def server():
    # define server IP address
    SERVER_IP='127.0.0.1'
    # Define server port address
    SERVER_PORT=12345
    SERVER_MONITOR_PORT=12346

    with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as monitor:
        # set socket options, SO_REUSEADDR specifies that the local 
        # address to which the socket binds can be reused
        monitor.setsockopt (socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        # Bind server to the address
        monitor.bind((SERVER_IP,SERVER_MONITOR_PORT))
        monitor.listen(6)

        # Initialize server
        with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as server:
            # notify server started
            print("Server started")
            
            # set socket options, SO_REUSEADDR specifies that the local 
            # address to which the socket binds can be reused
            server.setsockopt (socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

            # Bind server to the address
            server.bind((SERVER_IP,SERVER_PORT))

            print ("Server socket binded to %s" %(SERVER_PORT))

            # put the socket into listening mode, Its backlog parameter 
            # specifies the number of unaccepted connections that the 
            # system will allow before refusing new connections.
            server.listen(6)	
            print ("Server is waiting for client request...")	

            while True:
                # establish connection with client
                conn,addr=server.accept()
                conn2,addr2=monitor.accept()

                newThread = ConnectionThread (conn, addr)
                newThread2 = MonitorThread (conn2, addr2)
                newThread.start()
                newThread2.start()


# Main function
if __name__=='__main__':
    server()
