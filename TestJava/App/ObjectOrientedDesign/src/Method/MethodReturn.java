package Method;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Method Return

    Modifiers, return types, and parameter names are not part of the signature.

    The signature of a method uniquely identifies the method within a class.
    It is not allowed to have more than one method in a class with the same signature.

    The code for the method is specified in the method's body, which is enclosed in braces.

    A method is invoked using its name with the values for its parameters, if any, within parentheses.

    To call the add method, use the following statement:

        add( 10, 12 );

    The above call to the add method passes 10 and 12 as the values for parameters n1 and n2, respectively.

    The two values, 10 and 12, that are used to call the add method are called actual parameters.

    Java copies the actual parameters to the formal parameters
    before it executes the code inside the body of the method.

    A return statement is used to return a value from a method. It starts with the return keyword.

    If a method returns a value, the return keyword must be followed by an expression,
    which evaluates to the value being returned.

    If the method does not return a value, its return type is specified as void.
    If the method's return type is void, the method does not have to include a return statement.

    If a method with a void return type wants to include a return statement,
    the return keyword must not be followed by any expression;
    the return keyword is immediately followed by a semicolon to mark the end of the statement.


    Return

    A return statement returns the control to the caller of the method.
    A return statement is the last statement that is executed in a method's body.

    To capture the value of a method call, use the method call expression anywhere you can use a value.

    For example, the following code assigns the value returned from the add method to a variable call sum:

        int sum = add( 10, 12 ); // sum variable will be assigned 22

    The following method declaration for a method printMessage;

        void printMessage() {
              System.out.println( "test" );
        }

    The printMessage method specifies void as its return type,
    which means that it does not return a value to its caller.

    It does not specify any parameters, which means it does not accept any input values from its caller.

    To call the printMessage method, write the following statement:

        printMessage();

    Since the printMessage() method does not return any value,
    you cannot use a call to this method as part of any expression where a value is expected.

    When a method's return type is void,
    it is not necessary to use a return statement because we do not have a value to return from the method.
 */

public class MethodReturn
{
}
