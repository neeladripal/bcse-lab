import math

def check_square (x) :
	"Function to check if the number is a odd square"
	y = int (math.sqrt(x))
	return y * y == x

# input the list of numbers
print ("Enter list of numbers: ", end = " ")
nums = list (map (int, input().split()))

# filter out the odd numbers
odd_nums = filter (lambda x: x%2 == 1, nums)

# filter out the odd squares
odd_squares = list (filter (check_square, odd_nums))

print ("Odd squares are: ", odd_squares)