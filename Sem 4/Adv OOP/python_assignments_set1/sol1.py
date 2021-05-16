def gen_primes():
    """ Generates an infinite sequence of prime numbers.
    """
    # Maps composites to primes witnessing their compositeness.
    # This is memory efficient, as the sieve is not "run forward"
    # indefinitely, but only as long as required by the current
    # number being tested.
    #
    sieve = {}
    
    # The running integer that's checked for primeness
    q = 2
    
    while True:
        if q not in sieve:
            # q is a new prime.
            # Yield it and mark its first multiple that isn't
            # already marked in previous iterations
            # 
            yield q
            sieve[q * q] = [q]
        else:
            # q is composite. D[q] is the list of primes that
            # divide it. Since we've reached q, we no longer
            # need it in the map, but we'll mark the next 
            # multiples of its witnesses to prepare for larger
            # numbers
            # 
            for p in sieve[q]:
                sieve.setdefault(p + q, []).append(p)
            del sieve[q]
        
        q += 1

# take the number as input from user upto which prime numbers are to be generated
n = int (input ("Enter upper limit: "))
print ("List of prime numbers upto %d: " % (n))

# call the generator function to yield prime numbers upto n values
for value in gen_primes ():
	if value > n:
		break
	print (value, end = " ")
print ("")