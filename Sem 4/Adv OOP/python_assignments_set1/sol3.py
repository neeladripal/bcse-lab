from itertools import compress

# list of numbers from 0 to 21
Numbers =[i for i in range (22)]

# list of selectors for the first 10 odd values
odd_selectors = [x % 2 for x in Numbers]

# list of selectors for the first 10 even values
even_selectors = [(x + 1) % 2 for x in Numbers]

# iterable containing the first 10 odd values
Odd_list = compress (Numbers, odd_selectors)

print ("First 10 odd numbers: ")
for each in Odd_list:
	print (each, end = " ")
print ("")

# iterable containing the first 10 even values
Even_list = compress (Numbers, even_selectors)

print ("First 10 even numbers: ")
for each in Even_list:
	print (each, end = " ")
print ("")