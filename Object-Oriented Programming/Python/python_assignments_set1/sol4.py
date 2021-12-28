import re
phno = input ("Enter phone number: ")

# define the regex expression
# country code is optional
# country code can be 0 or +91
# phone number is of 10 digits
# first digit can be anything between 6 and 9
# rest 9 digits can be anything between 0 and 9
x = re.search ("^((\+91|0)?[6-9]{1}\d{9}){1}$", phno)

if x == None:
	print ("Not a valid Indian phone number")
else:
	print ("Valid Indian phone number")