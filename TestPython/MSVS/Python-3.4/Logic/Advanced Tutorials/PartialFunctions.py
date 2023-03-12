# Partial functions

# You can create partial functions in python by using the partial function from the functools library.

# Partial functions allow one to derive a function with x parameters to a function with fewer parameters
# and fixed values set for the more limited function.

# Import required:
from functools import partial

# Example: from functools import partial
def multiply(x,y): return x * y

# create a new function that multiplies by 2
dbl = partial(multiply, 2)
print ( dbl(4) )
#output: 8

# This code will return 8.
# An important note: the default values will start replacing variables from the left.
# The 2 will replace x. y will equal 4 when dbl(4) is called.
# It does not make a difference in this example, but it does in the example below.

# Edit the function provided by calling partial() and replacing the first three variables in func().
# Then print with the new partial function using only one input variable so that the output equals 60.
def func(u, v, w, x):
    return u*4 + v*3 + w*2 + x

p = partial(func, 5, 6, 7)
print ( p(8) )
#output: 60

