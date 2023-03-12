# Decorators

# Decorators allow you to make simple modifications to callable objects like functions, methods, or classes.
# We shall deal with functions for this tutorial.
# The syntax

@decorator
def functions(arg):
    return "Return"

# Is equivalent to:
def function(arg):
    return "Return"
function = decorator(function) #this passes the function to the decorator, and reassigns it to the functions

# As you may have seen, a decorator is just another function which takes a functions and returns one.
# For example you could do this:

def repeater(old_function):
    def new_function(*args, **kwds): #See learnpython.org/page/Multiple%20Function%20Arguments for how *args and **kwds works
        old_function(*args, **kwds) #we run the old function
        old_function(*args, **kwds) #we do it twice
    return new_function #we have to return the new_function, or it wouldn't reassign it to the value

# This would make a function repeat twice.
@repeater
def Multiply(num1, num2):
    print ( num1 * num2 )

Multiply(2, 3)
#output: 6
#        6

# You can also make it change the output
def Double_Out(old_function):
    def new_function(*args, **kwds):
        return 2*old_function(*args, **kwds) #modify the return value
    return new_function

# change input
def Double_In(old_function):
    def new_function(arg): #only works if the old function has one argument
        return old_function(arg*2) #modify the argument passed
    return new_function

# and do checking.
def Check(old_function):
    def new_function(arg):
        if arg<0: raise ValueError, "Negative Argument" #This causes an error, which is better than it doing the wrong thing
        old_function(arg)
    return new_function

# Let's say you want to multiply the output by a variable amount.
# You could do
def Multiply(multiplier):
    def Multiply_Generator(old_function):
        def new_function(*args, **kwds):
            return multiplier*old_function(*args, **kwds)
        return new_function
    return Multiply_Generator #it returns the new generator

# Now, you could do
@Multiply(3) #Multiply is not a generator, but Multiply(3) is
def Num(num):
    return num

# You can do anything you want with the old function, even completely ignore it!
# Advanced decorators can also manipulate the doc string and argument number.
# For some snazzy decorators, go to http://wiki.python.org/moin/PythonDecoratorLibrary. Exercise

# Make a decorator factory which returns a decorator that decorates functions with one argument.
# The factory should take one argument, a type, and then returns a decorator that makes function should check if the input is the correct type.
# If it is wrong, it should print "Bad Type". (In reality, it should raise an error, but error raising isn't in this tutorial.)
# Look at the tutorial code and expected output to see what it is if you are confused (I know I would be.)
# Using isinstance(object, type_of_object) or type(object) might help.


def type_check(correct_type):
    def new_function(old_function):
        def another_newfunction(arg):
            if(isinstance(arg, correct_type)):
                return old_function(arg)
            else:
                print ("Bad Type")
        return another_newfunction
    return new_function


@type_check(int)
def times2(num):
    return num*2

print ( times2(2) )
print ( times2('Not A Number') )

@type_check(str)
def first_letter(word):
    return word[0]

print ( first_letter('Hello World') )
first_letter( ['Not', 'A', 'String'] )
#output: 4
#        Bad Type
#        None
#        H
#        Bad Type


# Example : callable objects
class Verbose:
	def __init__(self, f):
		print ( "Initializing Verbose." )
		self.func = f;

	def __call__(self, *args, **kwargs):  #���� 
		print ( "Begin", self.func.__name__ )
		self.func(*args, **kwargs);    #����
		print ( "End", self.func.__name__ )

@Verbose
def my_function(name):   #l ���ڸ� ���� �Լ�
    print ( "hello,", name )

my_function( "Hi !!!" )
#output: Initializing Verbose.
#        ('Begin', 'my_function')
#        ('hello,', 'Hi !!!')
#        ('End', 'my_function')


class Greet(object):
    current_user = None
    def set_name(self, name):
        if name == 'admin':
            self.current_user = name
        else:
            raise Exception("Permission error !!!")

    def get_greeting(self, name):
        if name == 'admin':
            return "Hello {}".format(self.current_user)

greet = Greet()
greet.set_name('eunwoo')
#output: Traceback (most recent call last):
#        File "prog.py", line 14, in <module>
#        File "prog.py", line 7, in set_name
#        Exception: Permission error !!!