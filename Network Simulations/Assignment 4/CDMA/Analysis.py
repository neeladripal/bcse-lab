class Report:
    def __init__(self, pktCount:int, totalTime:float):
        self.pktCount       = pktCount
        self.totalTime      = totalTime

    # Function to store analysis of transmission into specified file
    def storeReport(self, totalSender:int):

        # Calculate average statistics for each station
        avgPktCount = int(self.pktCount/totalSender)
        avgTotalTime = self.totalTime
        
        # Open the file
        file=open("results.txt",'a')
        
        # Write different parameters of analysis into the file
        file.writelines("\nTest run with {:d} senders--------------------\n".format(totalSender))
        file.writelines('Total packets sent = {} per sender\n'.format(avgPktCount))
        file.writelines('Total time taken = {:6.6f} seconds\n'.format((avgTotalTime)))
        effectiveBandwidth = (self.pktCount/self.totalTime)
        file.writelines('Effective bandwidth = {:d} bps\n'.format(int(effectiveBandwidth)))
        stt = (self.totalTime/avgPktCount)
        file.writelines('Average Delay per packet = {:6.6f} seconds\n'.format(stt))
        file.writelines("\n")

        # Close the file
        file.close()