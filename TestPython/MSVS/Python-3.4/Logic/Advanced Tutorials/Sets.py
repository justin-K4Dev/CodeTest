
# Sets

# Sets are lists with no duplicate entries.
# Let's say you want to collect a list of words used in a paragraph:

print ( set( "my name is Eric and Eric is my name".split() ) )
#output: [ "my", "name", "is", "Eric", "and" ]

# This will print out a list containing "my", "name", "is", "Eric", and finally "and".
# Since the rest of the sentence uses words which are already in the set, they are not inserted twice.

# Sets are a powerful tool in Python since they have the ability to calculate differences and intersections between other sets.
# For example, say you have a list of participants in events A and B:
a = set(["Jake", "John", "Eric"])
b = set(["John", "Jill"])

# To find out which members attended both events, you may use the "intersection" method:
print ( a.intersection(b) )
#output: set(['John'])
print ( b.intersection(a) )
#output: set(['John'])

# To find out which members attended only one of the events, use the "symmetric_difference" method:
print ( a.symmetric_difference(b) )
#output: set(['Jill', 'Jake', 'Eric'])
print ( b.symmetric_difference(a) )
#output: set(['Jill', 'Jake', 'Eric'])

# To find out which members attended only one event and not the other, use the "difference" method:
print ( a.difference(b) )
#output: set(['Jake', 'Eric'])
print ( b.difference(a) )
#output: set(['Jill'])

# To receive a list of all participants, use the "union" method:
print ( a.union(b) )
#output: set(['Jill', 'Jake', 'John', 'Eric'])





