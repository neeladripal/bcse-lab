import socket
import time
from threading import Thread
from sender import Sender
from receiver import Receiver

class Client (Thread):
    def __init__ (self, id, type):
        Thread.__init__ (self)
        self.id = id
        self.type = type

    def run (self):
        SERVER_IP='127.0.0.1'
        # define server port address
        SERVER_PORT=12345
        SERVER_MONITOR_PORT=12346

        with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as monitor:
            monitor.connect((SERVER_IP, SERVER_MONITOR_PORT))

            # start the client socket
            with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as client:

                client.connect((SERVER_IP, SERVER_PORT))

                # recieve connection acknowledgement from server
                msg =  client.recv(1024).decode()  
                print("From Server :" , msg)

                # take the client name as input and send it to server
                clientName='#'.join([self.type, str(self.id)])

                client.sendall (bytes(clientName,'UTF-8'))

                # get client port number from server
                selfAddress = int(client.recv(1024).decode())
                
                if (self.type == "sender"):
                    client.send(str.encode("request for sending"))
                    receiver = client.recv(1024).decode().split("$")
                    print ("Receiver: ", receiver)
                    receiverName = receiver[0]
                    receiverAddress = int(receiver[1])

                    # data file name where data is stored
                    file_name="from.txt"

                    # initialize sender object
                    my_sender=Sender(client,monitor,clientName,selfAddress,receiverName,receiverAddress,file_name)

                    # mark the start of sending
                    print(clientName, "is sending to", receiverName)
                    
                    # Receive 'start' signal from channel for synchronization
                    data=client.recv(1024).decode()

                    # start transmission (using sender object)
                    my_sender.transmit()

                    # set and print notification from server about data transfer complition
                    data=client.recv(1024).decode()

                else:
                    client.send(str.encode("request for receiving"))
                    sender = client.recv(1024).decode().split("$")
                    senderName = sender[0]
                    senderAddress = int(sender[1])
                    
                    # file name where received data will be stored
                    file_name = "to.txt"
                    
                    # initialize receiver object
                    my_receiver=Receiver(client,monitor,clientName,selfAddress,senderAddress,file_name)
                    
                    # mark the start of sending
                    print(clientName, "is receiving from", senderName)

                    # Receive 'start' signal to channel for synchronization
                    client.send (bytes("start", 'utf-8'))

                    # start data receiving through receiver object
                    my_receiver.startReceiving()

                client.send(str.encode("close"))

            monitor.send(str.encode("close"))

# Main function
if __name__=='__main__':
    TOTAL_SENDER=4

    receivers = []
    senders = []

    for i in range (TOTAL_SENDER):
        newThread = Client (i, "receiver")
        receivers.append (newThread)
        newThread.start()

    time.sleep(0.2)
    for i in range (TOTAL_SENDER):
        newThread = Client (i, "sender")
        senders.append (newThread)
        newThread.start()

    for i in range (TOTAL_SENDER):
        receivers[i].join()
    
    for i in range (TOTAL_SENDER):
        senders[i].join()