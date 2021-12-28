def gp (a, q) :
	"Generates a series of geometric progression until term value exceeds 100000"
	try:
		while True:
			if a > 100000:
				return a
			yield a
			a *= q
	except ValueError as e:
		print (e)

# input first term and common ratio
a, q = map (int, input("Enter first term and common ratio: ").split())

# display the progression
print ("Geometric Progression with first term {0} and common ratio {1} -->".format (a, q))
for term in gp(a, q):
	print (term, end = " ")
print ("")