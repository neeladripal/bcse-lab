from errorMechanisms import CRC

# CRC polynomial (CRC-32-IEEE 802.3)
crc32key = '100000100110000010001110110110111'

# define frame structure and functionalities
class Frame:
    def __init__(self, source:int, destination:int, _type:int, seqNo:int, segmentData:str):
        self.source = source
        self.destination = destination
        self.type = _type 
        self.segmentData = segmentData
        self.seqNo = seqNo

    def toBinaryString(self, data_size:int):
        """Function to convert frame into binary string"""
        # initialize preamble and sfd
        preamble = '01'*28 
        sfd = '10101011' 

        # convert source and destination address into binary strings
        destAddress = '{0:048b}'.format(self.destination)
        sourceAddress = '{0:048b}'.format(self.source)

        # convert frame type into 8 bit binary string
        typeToBits = '{0:08b}'.format(self.type)

        # convert sequence no into 8 bit binary string
        seqToBits = '{0:08b}'.format(self.seqNo)

        segmentData = self.segmentData
        # pad the segment data if needed
        if(len(segmentData)<data_size):
            segmentData += '\0'*(data_size-len(segmentData))

        # for each character in data, convert into equivalent ASCII code and build the final binary string
        data = ""
        for i in range(0, len(segmentData)):
            character = segmentData[i]
            dataByte = '{0:08b}'.format(ord(character))
            data = data + dataByte

        # add the parts to get the final frame
        frame = preamble + sfd + destAddress + sourceAddress + typeToBits + seqToBits + data 

        # calculate the codeword using CRC-32 key   
        frame = CRC(crc32key).getCodeword(frame)
        self.frame = frame

        # return frame
        return frame

    
    @classmethod
    def build(cls,frame):
        """Function to convert binary string into frame object"""
        # get source and destination addresses
        source = int(frame[64:112],2)
        destination = int(frame[112:160],2)

        # get type of frame
        _type=int(frame[160:168],2)

        # get sequence number of frame
        seq_no=int(frame[168:176],2)

        # break data portion into 8-bit parts
        # for each such 8-bit binary string find the equivalent ASCII character
        text = ""
        data = frame[176:-32]
        asciiData = [data[i:i+8] for i in range(0,len(data),8)]
        for letter in asciiData:
            # Skip padded null data
            if(letter != '00000000'):
                text += chr(int(letter,2))

        # initialize new frame with above elements and return it
        new_frame = cls(source,destination,_type,seq_no,text)
        new_frame.frame = frame
        return new_frame
    
    def getData(self):
        """Function to extract data"""
        return self.segmentData
    
    def getType(self):
        """Function to extract type"""
        return self.type

    def getSeqNo(self):
        """Function to extract sequence number"""
        return self.seqNo

    def hasError(self):
        """Function to check error using binary string formed frame"""
        return not CRC(crc32key).checkCodeword(self.frame)

































# Just testing
# if __name__=='__main__':
#     seq=int(input('Enter sequence number : '))
#     _type=int(input('Enter type of the frame : '))
#     data=input('Enter 46 character string : ')
#     frame=frame(_type,seq,data)
#     new_=frame.toBinaryString()
#     new_=str.encode(new_)
#     new_=new_.decode()
#     new_frame=Frame.build(new_)
#     print('Data : ',new_frame.getData())
#     print('Sequence number : ',new_frame.getSeqNo())
#     print('Type : ',new_frame.getType())
#     if(new_frame.hasError()==False):
#         print('No error')
