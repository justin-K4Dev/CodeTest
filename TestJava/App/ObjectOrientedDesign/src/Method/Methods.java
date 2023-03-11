package Method;

/**
 * Created by justin on 2015-08-03.
 */

/*
    Methods

    A method in a class defines the behavior of the objects.
    A method is a named block of code.

    The code that invokes the method is the caller of the method.
    Optionally, a method may accept input values from the caller and it may return a value to the caller.

    The list of input values is known as parameters.
    A method may have zero parameters.
    If a method has zero parameters,
    we say that method does not have any parameters or method does not take any parameters.

    A method is always defined inside the body of a class.

    The general syntax for a method declaration is of the form

        <modifiers> <return type> <method name> (<parameters list>) <throws clause> {
            // Body of the method goes here
        }

        * <modifiers> is an optional list of modifiers;
        * <return type> is the data type of the value returned from the method;
        * <method name> is the name of the method.


    Method Parameters

    The method name is followed by a pair of opening and closing parentheses.
    Optionally, we can specify one or more parameters to the method within the parentheses.

    Multiple parameters are separated by a comma.
    The closing parenthesis may optionally be followed by a throws clause.

    Finally, we specify the code for the method inside opening and closing braces.

    The four parts in a method declaration are mandatory:

        * the return type,
        * method name,
        * a pair of opening and closing parentheses, and
        * a pair of opening and closing braces.

    The following is an example of a method:

        * it is named add;
        * it takes two parameters of type int named n1 and n2, and
        * it returns their sum:

        int add( int n1, int n2 ) {
            int sum = n1 + n2;
            return sum;
        }

    Sometimes, a method does not return a value to its caller.
    The keyword void is used as the return type if a method does not return any value to the caller.

    The method name must be a valid Java identifier.

    Conventionally, a Java method starts with a lowercase and subsequently a word cap is used.

    For example, getName, setName, getDogCount, and createDog are valid method names.

    A method may take input values from its caller. A parameter is used to take an input value from the caller.

    A parameter consists of two parts: a data type and a variable name. A method parameter is a variable declaration.

    The variables are used to hold the input values that are passed from the method's caller.
    A comma separates two parameters of a method.

    In the following example, the add method declares two parameters, n1 and n2.
    Both parameters are of the int data type.

        int add( int n1, int n2 )  {
            int sum = n1 + n2;
            return sum;
        }

    When the add method is called, the caller must pass two int values.

    The first value passed from the caller is stored in n1, and the second value passed from the caller is stored in n2.

    The parameters n1 and n2 are also known as formal parameters.

    A method is uniquely identified by its signature in a particular context.
    The signature of a method is the combination of its name and its parameter's number, types, and order.


    Local Variables

    A variable declared inside a method, a constructor, or a block is called a local variable.

    A local variable declared in a method exists only for the duration the method is being executed.

    Because a local variable exists only for a temporary duration,
    it cannot be used outside the method, the constructor, or the block in which it is declared.

    The formal parameters for a method are treated as local variables.
    They are initialized with the actual parameter values when the method is invoked,
    and before the method's body is executed.

    You need to observe the following rules about the usage of local variables.

    Local variables are not initialized by default.
    A local variable cannot be accessed in the program until it is assigned a value.
    A local variable can be declared anywhere in the body of a method.
    However, it must be declared before it is used.
    A local variable hides the name of an instance variable and a class variable with the same name.
 */

public class Methods
{
}
