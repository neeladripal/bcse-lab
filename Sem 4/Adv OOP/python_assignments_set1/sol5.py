def gen_fibonacci ():
	"Generator function to generate an indefinite sequence of fibonacci numbers"
	a = 0
	b = 1

	while True:
		yield a
		c = a + b
		a = b
		b = c

print ("First seven fibonacci numbers: ")

i = 1
for num in gen_fibonacci ():
	# print the first 7 fibonacci numbers
	if i > 7:
		break
	print (num, end =" ")
	i += 1

print ("")
