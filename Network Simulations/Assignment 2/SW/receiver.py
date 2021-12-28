import time
from frameHelper import Frame

# Define Receiver class to handle data receiving 
class Receiver:
    def __init__(self, connection, name:str, senderAddress:int, receiverAddress:int, file:str):
        # get the client/receiver connection and other informations (name, data file name)
        self.connection         = connection
        self.name               = name
        self.filename          = file
        self.senderAddress      = senderAddress
        self.receiverAddress    = receiverAddress

        # some transmission control variables and flags
        self.frameType          = {'data' : 0, 'ack' : 1}
        self.seqNo              = 0
        self.recentACK          = Frame(senderAddress, receiverAddress, 1, 0, "Acknowledgement Frame")


    def sendAck(self):
        """Function for building and sending acknowledgement frame"""
        frame = Frame(self.senderAddress, self.receiverAddress, self.frameType['ack'],self.seqNo,'acknowledgement frame')
        self.recentACK = frame
        self.connection.send(str.encode(frame.toBinaryString(22)))


    def resendPreviousACK(self):
        """Function for resending previous acknowledgement frame if needed"""
        self.connection.send(str.encode(self.recentACK.toBinaryString(22)))
        
  
    def startReceiving(self):
        """# Function for receiving data"""
        time.sleep(0.4)

        # receive data from sender
        data = self.connection.recv(576).decode()

        # initialise total data received
        total_data = ""

        while data != "end":
            print("\nSTATUS: FRAME RECEIVED")
            
            # build frame from binary data string
            frame = Frame.build(data)
            
            # If frame has no error
            if not frame.hasError():
                print("STATUS: NO ERROR FOUND")             
                
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
                    print("STATUS: ACK SENT\n")

                # if sequence number is not what is required, resend the previous ACK 
                else:
                    self.resendPreviousACK()
                    print("STATUS: ACK RESENT")
            # discard erroneous frame
            else:
                print("STATUS: FRAME DISCARDED")

            # wait and receive next frame
            data = self.connection.recv(576).decode()

        file = open(self.filename,'w')
        file.write(total_data)
        file.close()