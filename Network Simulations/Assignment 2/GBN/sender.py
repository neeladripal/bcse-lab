import time
import threading
from frameHelper import Frame
import logger

# define maximum window size
MAX_WINDOW_SIZE = 7

# define time-out time in seconds
timeout=2

# store all the round-trip times
rttList = []

class Sender:
    def __init__(self, connection, name:str, senderAddress:int, receiverName:str, receiverAddress:int ,fileName:str):
        # get the client/receiver connection and other informations (name, data file name)
        self.connection = connection
        self.name = name
        self.receiver = receiverName
        self.fileName = fileName
        self.senderAddress = senderAddress
        self.receiverAddress = receiverAddress

        # some transmission control variables and flags
        self.frameType = {'data' : 0, 'ack' : 1}
        self.eot = False
        self.front = 0
        self.end = 0
        self.window_size = 0
        self.frameCount = 0
        self.totalFrameCount = 0
        self.current_window = [0 for i in range(0,8)]
        self.frame_timer = [0 for i in range(0,8)]
        self.lock  = threading.Lock()


    def isValidACK (self, ack_no:int):
        """Function to check if the acknowledgement number lies within window"""
        # if Ack is valid, return true
        if((self.front<ack_no and ack_no<=self.end) or (self.end<self.front and self.front<ack_no) or (ack_no<=self.end and self.end<self.front)):
            return True
        # if Ack number lies outside range, return false
        else:
            return False


    def resendFrames (self):
        """Function to handle frame resending"""
        time.sleep(0.2)

        # loop until end of transmission
        while (not self.eot) or (self.window_size>0):
            # if any frames were sent
            if(self.window_size>0):
                current_time = time.time()
                front_waiting_time = current_time - self.frame_timer[self.front]
                # if time-out occurs and there is a valid outstanding window
                # resend all the frames in the window again and restart timer
                if(front_waiting_time > timeout):
                    self.lock.acquire()
                    temp = self.front
                    while (temp != self.end):
                        # resend the frame
                        self.connection.send(str.encode(self.current_window[temp].frame))
                        print("STATUS: FRAME",temp,"RESENT")
                        
                        # restart the timer
                        self.frame_timer[temp] = time.time()
                        
                        # move to the next frame
                        temp = (temp+1)%(MAX_WINDOW_SIZE+1)
                        
                        # increment no of frames sent
                        self.totalFrameCount += 1
                    self.lock.release()


    def sendFrames(self):
        """Function to handle data sending"""
        time.sleep(0.2)
        
        # open data file for reading
        file = open(self.fileName,'r')

        # read data from file
        data = file.read(46)

        # loop until whole data is sent
        while data:
            # if window is not full, send another frame
            if (self.window_size<MAX_WINDOW_SIZE):
                # build frame using data, type and sequence number
                frame = Frame(self.senderAddress, self.receiverAddress, self.frameType['data'], self.end, data)

                # store current frame for re-transmission (if needed)
                self.current_window[self.end] = frame

                # acquire window write lock
                self.lock.acquire()

                # Send the frame
                self.connection.send(str.encode(frame.toBinaryString(46)))
                
                print("\nSTATUS: FRAME",self.end,"SENT TO CHANNEL")

                self.frame_timer[self.end] = time.time()

                # update end, window size and other parameters accordingly
                self.end = (self.end+1)%(MAX_WINDOW_SIZE+1)
                self.window_size += 1
                self.frameCount += 1
                self.totalFrameCount += 1

                # Read next data frame
                data = file.read(46)

                # release window write lock
                self.lock.release()

            # If all data has been read, break
            if len(data) == 0: break
        
        # Set the end-transmitting flag True
        self.eot = True

        # Close the data file
        file.close()


    def receiveAck(self):
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

            # if frame type is acknowledgement
            if frame.getType() == 1:
                # if frame has no error
                if(frame.hasError()==False):
                    
                    if self.isValidACK(frame.seqNo):
                        # Acquire lock for accessing window
                        self.lock.acquire()

                        # update the window front and window size according to the ackNo
                        while(self.front!=frame.seqNo):
                            roundTripTime = time.time() - self.frame_timer[self.front]
                            rttList.append(roundTripTime)

                            print("STATUS: FRAME",self.front,"HAS REACHED SUCCESSFULLY\n")
                            self.front = (self.front+1)%(MAX_WINDOW_SIZE+1)
                            self.window_size -= 1

                        # Release window access lock
                        self.lock.release()

                    else:
                        print("STATUS: WRONG ACK")
                else:
                    print("STATUS: ERRONEOUS ACK")
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
        receiveAckThread = threading.Thread(name="receiveAckThread", target=self.receiveAck)

        # create frame resending thread
        resendThread = threading.Thread(name="resendThread",target=self.resendFrames)

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
        logger.storeLogs(self.name, self.receiver, self.frameCount, self.totalFrameCount, totalTime, rttList)