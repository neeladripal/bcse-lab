import random

# inject error in binary string
# if burst length provided, flip bits randomly within a 
# window of that length, else choose the length randomly
def injectError (data, errLength = -1, burst = False):
    # convert to list
    s = list(data)
    l = len(s)

    # if error length not provided, generate randomly
    if errLength < 0 or errLength > l:
        if burst == True:
            errLength = random.randint(2, l)
        else:
            errLength = random.randint(1, l)

    # decide the left and right indices for the error window
    left = random.randint(0, l - errLength)
    right = left + errLength - 1

    s[left] = '0' if s[left] == '1' else '1'
    s[right] = '0' if s[right] == '1' else '1'
    left += 1
    
    # flip random bits within the window
    while left < right:
        if random.randint(0,1) == 1 :
            s[left] = '0' if s[left] == '1' else '1'
        left += 1

    # convert to string
    errorData = ''.join(s)
    return errorData

# Function to inject single bit error in binary string
def injectSingleError (data):
    return injectError(data, 1)

# Function to inject burst error in binary string
def injectBurstError (data, errLength = -1):
    return injectError(data, errLength, True)