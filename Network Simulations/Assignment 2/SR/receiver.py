import time
import threading
from frameHelper import Frame

# define window size
WINDOW_SIZE = 8

# define maximum sequence number
MAX_SEQUENCE_NUMBER = 16

class Receiver:
    def __init__(self, connection, name:str, senderAddress:int, receiverAddress:int, file:str):
        # get the client/receiver connection and other informations (name, data file name)
        self.connection = connection
        self.name = name
        self.filename = file
        self.senderAddress = senderAddress
        self.receiverAddress = receiverAddress

        # some transmission control variables and flags
        self.frameType = {'data' : 0, 'ack' : 1, 'nak' : 2}
        self.front = 0
        self.end = WINDOW_SIZE
        self.window = [0 for i in range (0, MAX_SEQUENCE_NUMBER)]
        self.filled_up = [False for i in range (0, MAX_SEQUENCE_NUMBER)]
        self.nakSent = False
        self.ackSent = False
        self.recentACK = Frame(self.senderAddress, self.receiverAddress, 1, 0, "Acknowledgement Frame")
        self.eot = False
        self.lastACKsent = None


    def validSEQ(self,seq_no:int):
        """Function to check if the sequence number of incoming frame lies within window"""
        if((self.front<=seq_no and seq_no<self.end) or (self.end<self.front and self.front<=seq_no) or (seq_no<self.end and self.end<self.front)):
            return True
        else:
            return False


    def sendAck(self):
        """Function for building and sending ACK frame"""
        frame = Frame(self.senderAddress, self.receiverAddress, self.frameType['ack'],self.front,'acknowledgement frame')
        self.recentACK = frame
        print("Sent ACK",self.front)
        self.connection.send(str.encode(frame.toBinaryString(22)))
        self.lastACKsent = time.time()


    def sendNak(self):
        """Function for building and sending NAK frame"""
        frame = Frame(self.senderAddress, self.receiverAddress, self.frameType['nak'],self.front,'not acknowledgement')
        self.connection.send(str.encode(frame.toBinaryString(22)))
        print("Sent NAK",self.front)


    def resendPreviousACK(self):
        """Function for resending last ACK on timeout"""
        while(not self.eot):
            if (self.lastACKsent == None):
                continue
            elapsedTime = time.time() - self.lastACKsent
            if(elapsedTime > 1):
                self.connection.send(str.encode(self.recentACK.toBinaryString(22)))
                self.lastACKsent = time.time()
  

    def startReceiving(self):
        """Function for receiving frames"""
        time.sleep(0.4)

        ACKresendingThread = threading.Thread(target=self.resendPreviousACK)
        ACKresendingThread.start()

        # wait for data and receive
        data=self.connection.recv(576).decode()

        total_data = ""

        while data!="end":
            # build frame from binary data string
            frame = Frame.build(data)
            print("\nSTATUS: FRAME RECEIVED")

            if not frame.hasError():
                print("STATUS: NO ERROR FOUND")
                seqNo = frame.getSeqNo()

                # if frame other than first one got, send NAK
                if(seqNo!=self.front and self.nakSent==False):
                    self.sendNak()
                    self.nakSent = True
                
                # if seq no within the window accept it
                if(self.validSEQ(seqNo) and self.filled_up[seqNo]==False):
                    self.filled_up[seqNo] = True
                    self.window[seqNo] = frame.getData()
                    print(frame.getData())

                    # take the received data sequentially into the final data string
                    # update the front, end of the window accordingly (also update flags)
                    while(self.filled_up[self.front]==True):
                        total_data += self.window[self.front]
                        self.filled_up[self.front] = False
                        self.front = (self.front + 1)%MAX_SEQUENCE_NUMBER
                        self.end = (self.end + 1)%MAX_SEQUENCE_NUMBER
                        self.ackSent = True
                        print("STATUS: FRAME RECEIVED SUCCESSFULLY")

                    # if sequential frame received, send acknowledgement
                    if(self.ackSent):
                        self.sendAck()
                        self.ackSent = False
                        self.nakSent = False
            
            # discard erroneous frame
            else:
                print("STATUS: ERRONEOUS FRAME")

            # wait and receive next frame
            data=self.connection.recv(576).decode()

        # stop the resending-acknowledgement thread
        self.eot = True
        ACKresendingThread.join()

        # write the whole data into file
        file = open(self.filename,'w')
        file.write(total_data)
        file.close()
