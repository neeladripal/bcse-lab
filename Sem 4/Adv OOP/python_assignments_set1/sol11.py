print ("Pythagorean Triplets with smaller side upto 10 -->")
# form : (m^2 - n^2, 2*m*n, m^2 + n^2)
# generate all (m, n) pairs such that m^2 - n^2 <= 10
# if we take (m > n), for m >= 6, m^2 - n^2 will always be greater than 10
# so m ranges from 1 to 5 and n ranges from 1 to m-1
pythTriplets = [(m*m - n*n, 2*m*n, m*m + n*n) for (m,n) in [(x, y) for x in range (1, 6) for y in range (1, x)] if m*m - n*n <= 10]
print (pythTriplets)