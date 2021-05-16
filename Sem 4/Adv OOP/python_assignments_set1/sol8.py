N = 50
print ("Multiples of 5 upto %d -->" % (N))

multiples = list (filter (lambda x: (x % 5 == 0), [x for x in range (0, N+1)]))
print (multiples)