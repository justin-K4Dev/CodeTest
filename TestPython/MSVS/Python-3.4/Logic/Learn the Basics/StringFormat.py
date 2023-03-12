# String Format

# Python uses C-style string formatting to create new, formatted strings.
# The "%" operator is used to format a set of variables enclosed in a "tuple" (a fixed size list),
# together with a format string, which contains normal text together with "argument specifiers",
# special symbols like "%s" and "%d".
#
# Let's say you have a variable called "name" with your user name in it,
# and you would then like to print out a greeting to that user.


name = "John"
print ( "Hello, %s!" % name )
#output: Hello, John!


name = "John"
age = 23
print ( "%s is %d years old." % (name, age) )
#output: John is 23 years old.


mylist = [1,2,3]
print ( "A list: %s" % mylist )
#output: A list: [1, 2, 3]


# Here are some basic argument specifiers you should know:
#
# %s - String (or any object with a string representation, like numbers)
# %d - Integers
# %f - Floating point numbers
# %.<number of digits>f - Floating point numbers with a fixed amount of digits to the right of the dot.
# %x/%X - Integers in hex representation (lowercase/uppercase)

