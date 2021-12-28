import socket
import time
import pickle
import Analysis

# Define time slot
timeSlot = 0.05

# Define Sender class for data sending management
class Sender:
    # Function for initializing sender object
    def __init__(self, sender_no:int, fileName:str, walshCode):
        # Get the client/sender connection and other informations (name, receive name, data file name)
        self.connection         = 0 
        self.fileName           = fileName
        self.senderNo           = sender_no
        self.walshCode          = walshCode
        self.report             = 0
        self.pktCount           = 0

    def sendData(self):
        # Open data file
        file = open(self.fileName)
        
        # Read first byte of data
        byte = file.read(1)

        # loop until whole data is sent
        while byte:
            # Print coded data to be sent
            print('Sender ',self.senderNo,' is sending character : ',byte)

            # send the data bytes
            data = '{0:08b}'.format(ord(byte))
            
            # Convert character byte into code, 0 -> -1, 1 -> 1
            for i in range(len(data)):
                dataToSend = []
                dataBit = int(data[i])
                if dataBit == 0: dataBit = -1
               
                # Print data to be sent and walsh code
                print('Sender ',self.senderNo,' is sending data-bit : ',dataBit,' with Walsh-code : ',self.walshCode)

                # Build coded-data from Walsh Code
                for j in self.walshCode:
                    dataToSend.append(j * dataBit)

                # Print coded data to be sent
                print('Sender ',self.senderNo,' is sending coded data : ',dataToSend)

                # Send coded data to channel
                self.connection.send(pickle.dumps(dataToSend))
                self.pktCount += 1

                # Wait for next time slot
                time.sleep(timeSlot)

            byte = file.read(1)
            
        # Send 'end' signal to channel
        self.connection.send(pickle.dumps('end'))

    # Function to control the whole transmission
    def startTransmission(self):
        # Initialize the socket
        self.connection = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

        # Connect with the channel
        channel_ip = '127.0.0.1'
        channel_port = 12345
        self.connection.connect((channel_ip,channel_port))

        # Notify channel that it's a sender
        self.connection.send(str.encode('sender'))

        # Get sender number request and send it
        self.connection.recv(1024).decode()
        self.connection.send(str.encode(str(self.senderNo)))
        self.connection.recv(1024).decode()

        start_time = time.time()

        # Call the sending function
        self.sendData()

        end_time = time.time()

        # Close the connection
        self.connection.close()

        self.report = Analysis.Report(self.pktCount,(end_time-start_time))