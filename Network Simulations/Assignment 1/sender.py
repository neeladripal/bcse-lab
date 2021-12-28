# import the necessary modules
import socket
from threading import Thread, Lock
import errorMechanisms as em
import errorInjection as ei

lock = Lock ()          # to regulate the limit on number of active threads at a time

activeThreadCount = 0           # number of threads currently active
MAXIMUM_PROCESSING = 6          # maximum number of clients that can be served simultaneously
MAXIMUM_WAITING = 2             # maximum number of clients waiting to connect to server

# specify a host network interface, here we use loopback interface whose IPv4 address is 127.0.0.1
# If a hostname is used in the host portion of IPv4/v6 socket address, the program may show a
# non-deterministic behavior, as Python uses the first address returned from the DNS resolution
HOST = '127.0.0.1' 

# reserve a port on local machine for listening to incoming client requests
PORT = 12345

# original message to send
file = open("testdata.txt", "r")
message = file.read()
file.close()

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
        print ('\nGot new connection from', clientAddress)

    # override the run method to specify the code that the thread would run on
    def run (self) -> None:

        # send a message to indicate that the server is ready to respond
        self.csocket.send(bytes("You are now connected to server.\nWrite \"start\" to begin: ",'utf-8'))

        try:
            # a blocking call to receive message from checker in bytes form
            confirmation = self.csocket.recv(1024).decode()

            # receive the method from the server
            print ('From checker at', self.caddr[1], 'received:', confirmation)
            
            if confirmation == "start":
                global message
                PACKET_SIZE = 32

                # calculate no of datawords
                PACKET_COUNT = len(message) // PACKET_SIZE

                errMechanisms = ["VRC", "LRC", "CHECKSUM", "CRC"]
                errDetected = [0, 0, 0, 0]
                crc8key = "111010101"
                crc4key = "10101"
                errObj = [em.VRC(), em.LRC(8), em.CheckSum(8), em.CRC(crc8key)]
                
                for cnt in range(PACKET_COUNT):
                    # get the dataword from the message
                    dataword = message[cnt*PACKET_SIZE:(cnt+1)*PACKET_SIZE]
                    errDataword = ei.injectError(dataword)

                    # print ("\n%-25s %s" % ("Dataword:", dataword))
                    errCodewords = []
                    # obtain codewords for different checking mechanisms and inject error
                    for i in range(4):
                        # codeword = errObj[i].getCodeword(dataword)
                        # # print ("\n%-25s %s" % (errMechanisms[i] + " Codeword:", codeword))
                        # errCodeword = ei.injectError(codeword)
                        # # print ("%-25s %s" % (errMechanisms[i] + " ErrorCodeword:", errCodeword))
                        # errCodewords.append(errCodeword)
                        errCodewords.append(errDataword + errObj[i].generate(dataword))

                    # send the error injected codewords
                    self.csocket.sendall (bytes(" ".join(errCodewords), 'UTF-8'))
                    
                    # a blocking call to receive check ackword from checker in bytes form
                    ackword = self.csocket.recv(1024)
                    
                    # if the message contains no data, it must be due to some error
                    if not ackword:
                        break

                    # decode the ackword received from checker
                    ackword = ackword.decode ()
                    # print ('From checker at', self.caddr[1], 'received: ', ackword)

                    for i in range(4):
                        errDetected[i] += int(ackword[i])

                    if ackword[3] == '0':
                        print ("\nError not detected by CRC")
                        print ("%-20s %s" % ("Dataword:", dataword))
                        print ("%-20s %s" % ("CRC Codeword:", errCodewords[3]))

                    # if ackword[2] == '1' and ackword[3] == '0':
                    #     print ("\nError detected by checksum but not by CRC")
                    #     print ("%-20s %s" % ("Dataword:", dataword))
                    #     print ("%-20s %s" % ("Checksum codeword:", errCodewords[2]))
                    #     print ("%-20s %s" % ("CRC Codeword:", errCodewords[3]))

                    # if ackword[0] == '1' and ackword[3] == '0':
                    #     print ("\nError detected by VRC but not by CRC")
                    #     print ("%-20s %s" % ("Dataword:", dataword))
                    #     print ("%-20s %s" % ("VRC codeword:", errCodewords[0]))
                    #     print ("%-20s %s" % ("CRC Codeword:", errCodewords[3]))
                
                # print result with accuracy statistics
                result = "From checker at " + str(self.caddr[1]) + ", accuracy measured on " + str(PACKET_COUNT) + " packets: "
                for i in range(4):
                    accuracy = "{:.2f}".format(errDetected[i]/PACKET_COUNT * 100)
                    result += errMechanisms[i] + " (" + accuracy + "%) "
                print (result)

            else:
                print("Invalid confirmation message")

            # send 'end' message to denote end of codewords
            self.csocket.sendall (bytes('end', 'UTF-8'))
        
        except:
            print ('Cannot receive data')           # in case the client is abrubtly terminated
            
        # message to show that the client has been disconnected
        print ("Checker at", self.caddr, "disconnected")
        
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