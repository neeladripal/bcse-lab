class VRC():
    def generate (self, dataword):
        """Function to find the parity from a dataword"""
        parity = 0

        # Calculate parity of the dataword
        for i in dataword:
            parity = parity ^ int(i, 2)
        return bin(parity)[2:]

    def getCodeword (self, dataword):
        """Function to get the codeword"""
        extraBits = '0'
        return dataword + self.generate(dataword + extraBits)

    def checkCodeword (self, codeword):
        """Function to verify the parity"""
        parity = self.generate(codeword)

        # If parity is 0, no error detected
        if int(parity,2) == 0 :
            return True
        else:
            return False

class LRC():
    def __init__ (self, word_size):
        self.word_size = word_size

    def generate (self, dataword):
        """Function to find the LRC from a dataword"""
        k = self.word_size
        wordCount = len(dataword) // k

        # Calculate XOR of all k-bit words
        tmp = int('0', 2)
        for i in range(wordCount):
            tmp = tmp ^ int(dataword[i*k:(i+1)*k], 2)

        # Convert the result into binary and append 0s 
        # if needed to make it a k-bit word
        lrc = bin(tmp)[2:]
        if(len(lrc) < k):
            lrc = '0'*(k-len(lrc))+lrc

        return lrc

    def getCodeword (self, dataword):
        """Function to get the codeword"""
        extraBits = '0'*self.word_size
        return dataword + self.generate(dataword + extraBits)

    def checkCodeword (self, codeword):
        """Function to verify the LRC"""
        lrc = self.generate(codeword)

        # If the generated lrc is zero, no error detected
        if int(lrc, 2) == 0 :
            return True
        else:
            return False

class CheckSum():
    def __init__ (self, word_size):
        self.word_size = word_size

    def generate (self, dataword):
        """Function to find the Checksum from a Message"""
        k = self.word_size
        # Dividing sent message in words of k bits
        wordCount = len(dataword) // k

        # Calculating the binary sum of packets
        Sum = int ("0", 2)
        for i in range(wordCount):
            Sum += int(dataword[i*k:(i+1)*k], 2)
    
        Sum = bin(Sum)[2:]
    
        # Wrapping and adding the overflow bits
        if(len(Sum) > k):
            x = len(Sum)-k
            Sum = bin(int(Sum[0:x], 2)+int(Sum[x:], 2))[2:]
        if(len(Sum) < k):
            Sum = '0'*(k-len(Sum))+Sum
    
        # Calculating the complement of sum
        checksum = ''
        for i in Sum:
            if(i == '1'):
                checksum += '0'
            else:
                checksum += '1'
        return checksum

    def getCodeword (self, dataword):
        """Function to get the codeword"""
        extraBits = '0'*self.word_size
        return dataword + self.generate(dataword + extraBits)

    def checkCodeword (self, codeword):
        """Function to verify the checksum"""
        checksum = self.generate(codeword)

        if int(checksum, 2) == 0 :
            return True
        else:
            return False

class CRC():
    def __init__ (self, key):
        self.key = key
    
    def xor(self, a, b):
        """Returns XOR of 'a' and 'b' (both of same length)"""
        # initialize result
        result = []

        # Traverse all bits, if bits are
        # same, then XOR is 0, else 1
        for i in range(1, len(b)):
            if a[i] == b[i]:
                result.append('0')
            else:
                result.append('1')

        return ''.join(result)

    def generate (self, dividend):
        """Function to generate the CRC checkword by modulo-2 division"""
        divisor = self.key

        # Number of bits to be XORed at a time.
        k = len(divisor)

        # Slicing the dividend to appropriate
        # length for particular step
        tmp = dividend[0 : k]
        pick = k

        while pick < len(dividend):

            if tmp[0] == '1':

                # replace the dividend by the result
                # of XOR and pull 1 bit down
                tmp = self.xor(divisor, tmp) + dividend[pick]

            else: # If leftmost bit is '0'
                # If the leftmost bit of the dividend (or the
                # part used in each step) is 0, the step cannot
                # use the regular divisor; we need to use an
                # all-0s divisor.
                tmp = self.xor('0'*k, tmp) + dividend[pick]

            # increment pick to move further
            pick += 1

        # For the last n bits, we have to carry it out
        # normally as increased value of pick will cause
        # Index Out of Bounds.
        if tmp[0] == '1':
            tmp = self.xor(divisor, tmp)
        else:
            tmp = self.xor('0'*pick, tmp)

        checkword = tmp
        return checkword

    def getCodeword (self, dataword):
        """Function to get the codeword"""
        extraBits = '0' * (len(self.key) - 1)
        return dataword + self.generate(dataword + extraBits)

    def checkCodeword (self, codeword):
        """Function to verify the CRC"""
        rem = self.generate(codeword)

        # If the generated lrc is zero, no error detected
        if int(rem, 2) == 0 :
            return True
        else:
            return False