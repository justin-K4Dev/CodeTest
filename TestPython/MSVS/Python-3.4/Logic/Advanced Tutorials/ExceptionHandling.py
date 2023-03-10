# Exception Handling

# When programming, errors happen.
# It's just a fact of life. Perhaps the user gave bad input. Maybe a network resource was unavailable.
# Maybe the program ran out of memory.
# Or the programmer may have even made a mistake!

# Python's solution to errors are exceptions.
# You might have seen an exception before.

# >>> print a
# Traceback (most recent call last):
#   File "<stdin>", line 1, in <module>
# NameError: name 'a' is not defined

# Oops! Forgot to assign a value to the 'a' variable.
# But sometimes you don't want exceptions to completely stop the program.
# You might want to do something special when an exception is raised.
# This is done in a try/except block.

# Here's a trivial example:
# Suppose you're iterating over a list.
# You need to iterate over 20 numbers, but the list is made from user input, and might not have 20 numbers in it.
# After you reach the end of the list, you just want the rest of the numbers to be interpreted as a 0.
# Here's how you could do that:

def do_stuff_with_number(n):
    print ( n )

the_list = (1, 2, 3, 4, 5)

for i in range(20):
    try:
        do_stuff_with_number( the_list[i] )
    except IndexError: # Raised when accessing a non-existing index of a list
        do_stuff_with_number( 0 )

# There, that wasn't too hard! You can do that with any exception.
# For more details on handling exceptions, look no further than here

# Handle all the exceptions!
#Setup
actor = {"name": "John Cleese", "rank": "awesome"}

#Function to modify, should return the last name of the actor - think back to previous lessons for how to get it
def get_last_name():
    return actor["last_name"]

#Test code
get_last_name()
print ( "All exceptions caught! Good job!" )
print ( "The actor's last name is %s" % get_last_name() )