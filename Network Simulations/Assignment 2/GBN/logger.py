# function to log the analytics of communication
def storeLogs(senderName, receiverName, effectiveFrames, totalFrames, totalTime, rttStore:list):
    # frame size (IEEE 802.3 Ethernet Frame Format)
    FRAME_SIZE=72*8
    # define bandwidth (in bps)
    bandwidth = 4000

    logs = "Sender: "+senderName+" ----------------------- "+"Receiver: "+receiverName
    logs += "\nTotal frames sent = {}".format(totalFrames)
    logs += "\nEffective frames sent = {}".format(effectiveFrames)
    logs += "\nTotal time taken = {} seconds".format(int(totalTime))
    
    # performance metrics
    throughput = (effectiveFrames*FRAME_SIZE)/totalTime
    logs += "\nThroughput = {} bps".format(int(throughput))
    logs += "\nUtilization percentage = {:.2f} %".format((throughput/bandwidth)*100)
    logs += "\nTransmission time = {:.5f} seconds/frame\n\n".format(totalTime/effectiveFrames)

    # open the file
    file=open("logs.txt",'a')
    
    # append the logs to the file
    file.writelines(logs)
    
    # Close the file
    file.close()

    













    # Calculate round-trip time from the store
    # rtt = 0
    # for index in range(0,len(rttStore)):
    #    rtt += rttStore[index]
    # roundTripTime = (rtt/len(rttStore))

    # BD = (bandwidth*roundTripTime)
    # print('Round trip time = ',roundTripTime)
    # file.writelines('Bandwidth-Delay product = {:6d} bits\n'.format(int(BD)))