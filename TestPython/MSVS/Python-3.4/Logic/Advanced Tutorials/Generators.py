# Generators

# Generators are very easy to implement, but a bit difficult to understand.

# Generators are used to create iterators, but with a different approach.
# Generators are simple functions which return an iterable set of items, one at a time, in a special way.

# When an iteration over a set of item starts using the for statement, the generator is run.
# Once the generator's function code reaches a "yield" statement, the generator yields its execution back to the for loop,
# returning a new value from the set.
# The generator function can generate as many values (possibly infinite) as it wants, yielding each one in its turn.

# Here is a simple example of a generator function which returns 7 random integers:

import random

def lottery():
    # returns 6 numbers between 1 and 40
    for i in range( 6 ):
        w = random.randint( 1, 40 )
        yield w
        print ( "Call No:%d, Value:%d" % ( i, w ) )

    # returns a 7th number between 1 and 15
    z = random.randint( 1, 15 );
    yield z 
    print ( "Call 3 %d" % z )

for random_number in lottery():
    print ( "And the next number is... %d!" % random_number )

#output: And the next number is... 34!
#        Call No:0, Value:34
#        And the next number is... 32!
#        Call No:1, Value:32
#        And the next number is... 21!
#        Call No:2, Value:21
#        And the next number is... 4!
#        Call No:3, Value:4
#        And the next number is... 3!
#        Call No:4, Value:3
#        And the next number is... 21!
#        Call No:5, Value:21
#        And the next number is... 12!
#        Call 3 12

# This function decides how to generate the random numbers on its own,
# and executes the yield statements one at a time,
# pausing in between to yield execution back to the main for loop.