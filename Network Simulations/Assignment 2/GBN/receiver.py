import time
from frameHelper import Frame

# Define window size
WINDOW_SIZE = 8

class Receiver:
    def __init__(self, connection, name:str, senderAddress:int, receiverAddress:int, file:str):
        # get the client/receiver connection and other informations (name, data file name)
        self.connection = connection
        self.name = name
        self.filename = file
        self.senderAddress = senderAddress
        self.receiverAddress = receiverAddress

        # some transmission control variables and flags
        self.frameType = {'data' : 0, 'ack' : 1}
        self.seqNo = 0
        self.recentACK = Frame(self.senderAddress, self.receiverAddress, 1, 0, "Acknowledgement Frame")


    def sendAck(self):
        """Function for building and sending acknowledgement frame"""
        frame = Frame(self.senderAddress, self.receiverAddress, self.frameType['ack'],self.seqNo,'acknowledgement frame')
        self.recentACK = frame
        self.connection.send(str.encode(frame.toBinaryString(22)))
    

    def resendPreviousACK(self):
        """Function for resending previous acknowledgement frame if needed"""
        self.connection.send(str.encode(self.recentACK.toBinaryString(22)))
  

    def startReceiving(self):
        """Function for receiving data"""
        time.sleep(0.4)

        # Wait for data and receive
        data=self.connection.recv(576).decode()

        total_data = ""

        # If data-receiving hasn't ended yet 
        while data != "end":
            # Build frame from binary data string
            frame = Frame.build(data)
            print("\nSTATUS: FRAME RECEIVED")
            
            # If frame has no error
            if not frame.hasError():
                print("STATUS: NO ERROR FOUND")
                # get frame sequence number 
                seqNo = frame.getSeqNo()

                # if the ack no in received frame is equal to the expected
                if self.seqNo == seqNo:
                    data = frame.getData()
                    # print(data)
                    total_data += data
                    self.seqNo = (self.seqNo+1)%WINDOW_SIZE
                    self.sendAck()
                    print("STATUS: ACK SENT\n")

                else:
                    self.resendPreviousACK()
                    print("STATUS: ACK RESENT")
            # discard erroneous frame
            else:
                print("STATUS: FRAME DISCARDED")

            # wait and receive next frame
            data=self.connection.recv(576).decode()

        file = open(self.filename,'w')
        file.write(total_data)
        file.close()