import re
# dummy user data
userData = [("helo", "helo@x.com", 17), ("alex", "alex@y.com", -20), ("nova", "novaz.com", 20)]

# custom exception class
class NotUniqueUsernameException (Exception):
	def __init__ (self, name):
		self.name = name
	def __str__ (self):
		return "Username (%s) already exists." % (self.name)

# custom exception class
class NegativeAgeException (Exception):
	def __init__ (self, age):
		self.age = age
	def __str__ (self):
		return "Age (%d) cannot be negative." % (self.age)

# custom exception class
class UnderSixteenException (Exception):
	def __init__ (self, age):
		self.age = age
	def __str__ (self):
		return "Age (%d) under 16." % (self.age)

# custom exception class
class NotValidEmailException (Exception):
	def __init__ (self, email):
		self.email = email
	def __str__ (self):
		return "Email address (%s) is not valid email address" % (self.email)

# dictionary to store username & email as key, value if age >= 16
userDirectory = {}

for username, email, age in userData:
	try:
		if username in userDirectory:
			raise NotUniqueUsernameException (username)
		if age <= 0:
			raise NegativeAgeException (age)
		if age < 16:
			raise UnderSixteenException (age)
		x = re.search ("^(\w|\.|\_|\-)+[@](\w|\_|\-|\.)+[.]\w{2,3}$", email)
		if x == None:
			raise NotValidEmailException (email)
		userDirectory [username] = email

	except Exception as e:
		print (e, end = " ")
		print ("Username (%s) not stored" % username)

	else:
		print ("Username:%s stored" % username);

print ("Directory -->")
print (userDirectory)