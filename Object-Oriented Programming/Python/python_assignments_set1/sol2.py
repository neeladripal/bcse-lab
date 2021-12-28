# returns an array that represents the days of the week in the current locale
from calendar import day_name as dlist

# create an empty dictionary
dict = {}

i = 0

# append discount values to dict with day of week as key
for day in dlist:
    dict[day] = int (i * 2.4)
    i += 1

print (dict)