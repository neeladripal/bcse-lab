import random

# generate a random binary string
def generateMessage (size):
    message = ''
    for count in range(size):
        message += str(random.randint(0,1))

    return message

n = 32 * 10000       # size of data

file = open("testdata.txt", "w")
file.write(generateMessage(n))
file.close()