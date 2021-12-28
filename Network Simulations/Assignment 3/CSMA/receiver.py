import persistentMethods
import random
import time
from frameHelper import Frame

# Define Receiver class to handle data receiving 
class Receiver:
    def __init__(self, connection, monitor, name:str, receiverAddress:int, senderAddress:int, file:str):
        # get the client/receiver connection and other informations (name, data file name)
        self.connection         = connection
        self.monitor            = monitor
        self.name               = name
        self.filename           = file
        self.receiverAddress    = receiverAddress
        self.senderAddress      = senderAddress

        # some transmission control variables and flags
        self.frameType          = {'data' : 0, 'ack' : 1}
        self.seqNo              = 0
        self.recentACK          = Frame(receiverAddress, senderAddress, 1, 0, "Acknowledgement Frame")


    def checkBusyStatus (self):
        """Function to check if channel is busy for 1-persistent"""
        persistentMethods.pPersistent(self.monitor, 0.25)

    
    def sendAck(self):
        """Function for building and sending acknowledgement frame"""
        frame = Frame(self.receiverAddress, self.senderAddress, self.frameType['ack'],self.seqNo,'acknowledgement frame')
        self.recentACK = frame
        self.checkBusyStatus()
        self.connection.send(str.encode(frame.toBinaryString(22)))
        print(self.name, "STATUS: ACK SENT\n")


    def resendPreviousACK(self):
        """Function for resending previous acknowledgement frame if needed"""
        self.checkBusyStatus()
        self.connection.send(str.encode(self.recentACK.toBinaryString(22)))
        print(self.name, "STATUS: ACK RESENT")
        
  
    def startReceiving(self):
        """# Function for receiving data"""
        # receive data from sender
        data = self.connection.recv(576).decode()

        # initialise total data received
        total_data = ""

        while data != "end":
            if ("collision" not in data) and len(data) == 576:
                print("\n" + self.name + " STATUS: FRAME RECEIVED")
                
                # build frame from binary data string
                frame = Frame.build(data)
                
                # If frame has no error
                if not frame.hasError():
                    print(self.name, "STATUS: NO ERROR FOUND")             
                    
                    seqNo = frame.getSeqNo()
                    if self.seqNo == seqNo:
                        # extract data
                        data = frame.getData()
                        # print(data)
                        total_data += data
                        # update the sequence number of ACK
                        self.seqNo = (self.seqNo + 1) % 2
                        # send the corresponding ACK
                        self.sendAck()

                    # if sequence number is not what is required, resend the previous ACK 
                    else:
                        self.resendPreviousACK()
                # discard erroneous frame
                else:
                    print(self.name, "STATUS: FRAME DISCARDED")
            
            else:
                print(self.name, "STATUS: Collision detected")
                # random back-off time
                time.sleep (random.randint(0, 100) / 100)
                self.resendPreviousACK()

            # wait and receive next frame
            data = self.connection.recv(576).decode()

        file = open(self.filename,'w')
        file.write(total_data)
        file.close()