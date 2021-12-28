import time
import threading
from frameHelper import Frame
import logger

# define time-out time in seconds
timeout=2

# store all the round-trip times
rttList = []

# define Sender class for data sending management
class Sender:
    def __init__(self, connection, name:str, senderAddress:int, receiverName:str, receiverAddress:int, fileName:str):
        # get the client/receiver connection and other informations (name, data file name)
        self.connection         = connection 
        self.name               = name
        self.senderAddress      = senderAddress
        self.receiver           = receiverName
        self.receiverAddress    = receiverAddress
        self.fileName           = fileName

        # some transmission control variables and flags
        self.frameType          = {'data' : 0, 'ack' : 1}
        self.eot                = False
        self.seqNo              = 0
        self.frameCount         = 0
        self.totalFrameCount    = 0
        self.frameSent          = False
        self.sentTime           = 0
        self.receiveTime        = 0
        self.lock               = threading.Lock()

    def resendFrame(self):
        """Function to handle frame resending"""
        time.sleep(0.2)

        # loop until end of transmission
        while ((not self.eot) or self.frameSent):
            # if any frame was sent and ack not received
            if (self.frameSent):
                elapsedTime = time.time() - self.sentTime
                # if time-out occurs and there is a valid outstanding window
                # resend the frame in the window again and restart timer
                if (elapsedTime > timeout):
                    self.lock.acquire()
                    # resend the frame
                    self.connection.send(str.encode(self.lastFrame.toBinaryString(46)))
                    # update the sending time
                    self.sentTime = time.time()
                    print("STATUS: FRAME",self.frameCount,"RESENT")
                    self.totalframeCount += 1
                    self.lock.release()


    def sendFrame(self):
        """Function to send data"""
        time.sleep(0.2)
        
        # open data file for reading
        file = open(self.fileName,'r')
        # read the first data to be sent in a frame
        data = file.read(46)
        
        self.seqNo = 0
        self.frameCount = 0
        self.totalframeCount = 0

        # loop until whole data is sent
        while data:
            if(not self.frameSent):
                # build frame using data, type and sequence number
                frame = Frame(self.senderAddress, self.receiverAddress, self.frameType['data'], self.seqNo, data)
                # store current frame for re-transmission (if needed)
                self.lastFrame = frame

                # acquire the send lock
                self.lock.acquire()
                
                # send the frame and start sent-timer
                self.connection.send(str.encode(frame.toBinaryString(46)))
                
                self.sentTime = time.time()
                self.frameSent = True

                # update sequence number and other parameters accordingly
                self.seqNo = (self.seqNo+1)%2
                self.frameCount += 1
                self.totalframeCount += 1

                print("\nSTATUS: FRAME",self.frameCount,"SENT TO CHANNEL")

                # release the send lock
                self.lock.release()

                # read next data
                data = file.read(46)

                # if all data has been read, break
                if len(data) == 0: break
        
        # set the end of transmission flag to True
        self.eot = True

        # close the data file
        file.close()
        

    def receiveAck(self):
        """Function to receive ACK frame"""
        time.sleep(0.2)

        # loop until end of transmission
        while((not self.eot) or (self.frameSent)):
            # if a frame is sent
            if self.frameSent: 
                # wait and receive acknowledgement and build frame from that
                received = self.connection.recv(384).decode()
                # decode the received frame
                frame = Frame.build(received)
            else: continue

            # if frame type is acknowledgement, do the following
            if frame.getType() == 1:
                # if frame has no error, do the following
                if(frame.hasError()==False):
                    # if ACK_NO == SEQ_NO then receive it, stop timer(set the internal flag of time-out event)
                    if frame.seqNo == self.seqNo:
                        # store the round trip time
                        self.receiveTime = time.time()
                        
                        # evaluate the round trip time and append it to the list
                        roundTripTime = self.receiveTime - self.sentTime
                        rttList.append(roundTripTime)

                        print("STATUS: DATA HAS REACHED SUCCESSFULLY\n")
                        # unset the frameSent flag
                        self.frameSent = False 
                    else:
                        print("STATUS: WRONG ACK")
                else:
                    print("STATUS: ERRONEOUS ACK")
            else: 
                print("STATUS: RECEIVED FRAME IS NOT AN ACK")
            

    # Function to control the whole transmission
    def transmit(self):
        # Receive 'start' signal from channel for synchronization
        inp=self.connection.recv(1024)

        # mark the start of sending
        print("\nSender: "+self.name+" --------------- Receiver: "+self.receiver+"\n")

        # record the strating time
        startTime=time.time()

        # create a thread to handle data sending
        sendThread = threading.Thread(name="sendThread", target=self.sendFrame)
        
        # create another thread to handle acknowledgement receiving
        receiveAckThread = threading.Thread(name="receiveAckThread", target=self.receiveAck)

        # create frame resending thread
        resendThread = threading.Thread(name="resendThread",target=self.resendFrame)

        # start both the threads
        sendThread.start()
        receiveAckThread.start()
        resendThread.start()

        # wait for the threads to join (End their task)
        sendThread.join()
        receiveAckThread.join()
        resendThread.join()

        # notify channel about the end of transmission
        self.connection.send(str.encode("end"))

        totalTime = time.time() - startTime
        logger.storeLogs(self.name, self.receiver, self.frameCount, self.totalframeCount, totalTime, rttList)