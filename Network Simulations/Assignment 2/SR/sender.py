import time
import threading
from frameHelper import Frame
import logger

MAX_WINDOW_SIZE = 8
MAX_SEQUENCE_NUMBER = 16

# define time-out time in seconds
timeout=2

# store all the round-trip times
rttList = []

class Sender:
    def __init__(self, connection, name:str, senderAddress:int, receiverName:str, receiverAddress:int, fileName:str): 
        # get the client/receiver connection and other informations (name, data file name)
        self.connection = connection
        self.name = name
        self.receiver = receiverName
        self.fileName = fileName
        self.senderAddress = senderAddress
        self.receiverAddress = receiverAddress
        
        # some transmission control variables and flags
        self.frameType          = {'data' : 0, 'ack' : 1, 'nak' : 2}
        self.timeoutEvent       = threading.Event()
        self.eot                = False
        self.front              = 0
        self.end                = 0
        self.window_size        = 0
        self.frameCount         = 0
        self.totalFrameCount    = 0
        self.current_window     = [0 for i in range(0, MAX_SEQUENCE_NUMBER)]
        self.frameTimer         = [0 for i in range(0, MAX_SEQUENCE_NUMBER)]
        self.lock  = threading.Lock()
        self.oldestFrame        = 0


    def validACK(self,ack_no:int):
        """Function to check if the acknowledgement number lies within window"""
        if((self.front<ack_no and ack_no<=self.end) or (self.end<self.front and self.front<ack_no) or (ack_no<=self.end and self.end<self.front)):
            return True
        else:
            return False


    def resendFrames(self):
        """Function to handle frame resending on timeout"""
        time.sleep(0.2)

        # loop until end of transmission
        while (not self.eot) or (self.window_size>0):
            # if any frames were sent
            if(self.window_size>0):
                current_time = time.time()
                oldest_frame = 0
                max_waiting_time = 0
                temp = self.front

                # get the oldest frame in the current window
                while(temp!=self.end):
                    elapsedTime = current_time - self.frameTimer[temp]
                    if(elapsedTime > max_waiting_time):
                        max_waiting_time = elapsedTime
                        oldest_frame = temp
                    temp = (temp+1)%MAX_SEQUENCE_NUMBER
                
                # if time-out occurs and there is a valid outstanding window
                # resend the oldest frame again and restart its timer
                if(max_waiting_time > timeout):
                    # acquire the lock of window
                    self.lock.acquire()
                    if(self.current_window[oldest_frame]!=0):
                        self.connection.send(str.encode(self.current_window[oldest_frame].toBinaryString(46)))
                        
                        print("STATUS: FRAME",oldest_frame,"RESENT")
                        self.frameTimer[oldest_frame] = time.time()
                        self.totalFrameCount += 1

                    # release the lock of the window
                    self.lock.release()


    def sendFrames(self):
        """Function to handle data sending"""
        time.sleep(0.2)

        # mark the start of sending
        print("\n",self.name," starts sending data to ",self.receiver,"\n")
        
        # open data file for reading
        file = open(self.fileName,'r')

        # read data from file
        data_frame = file.read(46)

        # loop until whole data is sent
        while data_frame:
            # if window is not full, send another frame
            if (self.window_size < MAX_WINDOW_SIZE):
                # build frame using data, type and sequence number
                frame = Frame(self.senderAddress, self.receiverAddress, self.frameType['data'], self.end, data_frame)

                # store current frame for re-transmission (if needed)
                self.current_window[self.end] = frame

                # acquire window write lock
                self.lock.acquire()

                # send the frame
                self.connection.send(str.encode(frame.toBinaryString(46)))
                
                print("\nSTATUS: FRAME",self.end,"SENT TO CHANNEL")

                self.frameTimer[self.end] = time.time()

                # update end, window size and other parameters accordingly
                self.end = ((self.end+1)%MAX_SEQUENCE_NUMBER)
                self.window_size += 1
                self.frameCount += 1
                self.totalFrameCount += 1

                # read next data frame
                data_frame = file.read(46)

                # release window write lock
                self.lock.release()

            # if all data has been read, break
            if len(data_frame) == 0: break
        
        # set the end-transmitting flag True
        self.eot = True

        # close the data file
        file.close()


    def receiveAckOrNak(self):
        """Function to handle acknowledgement receiving"""
        time.sleep(0.2)

        # loop until end of transmission
        while (not self.eot) or (self.window_size>0):
            # if any frames were sent
            if(self.window_size>0): 
                # wait and receive acknowledgement and build frame from that
                received = self.connection.recv(384).decode()
                frame=Frame.build(received)
            else: continue

            # if frame type is ACK
            if frame.getType() == 1:
                # if frame has no error
                if(frame.hasError()==False):
                    if self.validACK(frame.seqNo):
                        # Acquire lock for accessing window
                        self.lock.acquire()

                        # update the window front and window size according to the ackNo
                        while(self.front!=frame.seqNo):
                            # Store round-trip time into the list
                            roundTripTime = time.time() - self.frameTimer[self.front]
                            rttList.append(roundTripTime)

                            print("STATUS: FRAME",self.front,"HAS REACHED SUCCESSFULLY\n")
                            self.current_window[self.front]=0
                            self.front = ((self.front+1)%MAX_SEQUENCE_NUMBER)
                            self.window_size -= 1

                        # release window access lock
                        self.lock.release()

                    else:
                        print("STATUS: WRONG ACK")
                else:
                    print("STATUS: ERRONEOUS ACK")
            
            # if frame type is NAK
            elif frame.getType() == 2:
                # if frame has no error
                if not frame.hasError():
                    # if requested sequence number is within window
                    if self.validACK(frame.seqNo):
                        # acquire lock for accessing window
                        self.lock.acquire()

                        # resend the requested frame
                        if(self.current_window[frame.seqNo]!=0):
                            self.connection.send(str.encode(self.current_window[frame.seqNo].toBinaryString(46)))
                            
                            print("STATUS: FRAME",frame.seqNo,"RESENT from NAK")
                            self.frameTimer[frame.seqNo] = time.time()
                            self.totalFrameCount += 1

                        # release window access lock
                        self.lock.release()
                    else:
                        print("STATUS: WRONG NAK")
                else:
                    print("STATUS: ERRONEOUS NAK")
            
            else: 
                print("STATUS: RECEIVED FRAME IS NOT AN ACK")
       

    def transmit(self):
        # Receive 'start' signal from channel for synchronization
        inp=self.connection.recv(1024)

        # mark the start of sending
        print("\nSender: "+self.name+" --------------- Receiver: "+self.receiver+"\n")

        # record the strating time
        startTime=time.time()

        # create a thread to handle data sending
        sendThread = threading.Thread(name="sendThread", target=self.sendFrames)
        
        # create another thread to handle acknowledgement receiving
        receiveThread = threading.Thread(name="receiveThread", target=self.receiveAckOrNak)

        # create frame resending thread
        resendThread = threading.Thread(name="resendThread",target=self.resendFrames)

        # start both the threads
        sendThread.start()
        receiveThread.start()
        resendThread.start()

        # wait for the threads to join (End their task)
        sendThread.join()
        receiveThread.join()
        resendThread.join()

        self.connection.recv(1024)

        # notify channel about the end of transmission
        self.connection.send(str.encode("end"))

        totalTime = time.time() - startTime
        logger.storeLogs(self.name, self.receiver, self.frameCount, self.totalFrameCount, totalTime, rttList)