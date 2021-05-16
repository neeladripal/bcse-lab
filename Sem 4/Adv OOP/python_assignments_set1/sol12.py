# define a list of all lowercase ASCII characters
chars = [chr (ord('a') + i) for i in range (26)]

# create enumerate object starting from 1
enumAscii = enumerate (chars, start = 1)
for item in enumAscii:
	print (item)