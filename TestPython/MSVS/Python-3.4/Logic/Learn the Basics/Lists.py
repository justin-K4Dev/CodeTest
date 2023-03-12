# Lists

# Lists are very similar to arrays.
# They can contain any type of variable, and they can contain as many variables as you wish.
# Lists can also be iterated over in a very simple manner.
# Here is an example of how to build a list.
mylist = []
mylist.append(1)
mylist.append(2)
mylist.append(3)
print( mylist[0] )
#output: 1
print( mylist[1] )
#output: 2
print( mylist[2] )
#output: 3

for x in mylist:
    print x
#output: 1,2,3,1,2,3


mylist = [1,2,3]
print( mylist[10] )
#output: Traceback (most recent call last):
#        File "prog.py", line 2, in <module>
#        IndexError: list index out of range