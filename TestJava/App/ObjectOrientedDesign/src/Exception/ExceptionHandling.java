package Exception;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Exception Handling

    An exception is a condition that may arise during the execution of a Java program
    when a normal path of execution is not defined.

    Java handles errors by separating the code that performs actions from the code that handles errors.

    When an exception occurs, Java creates an object with all pieces of information about the exception
    and passes it to the appropriate exception handling code.

    The information about an exception includes the type of exception,
    line number in the code where the exception occurred, etc.


    try-catch Block

    To handle exceptions, place the code in a try block. A try block looks like the following:

        try {
            // Code for the try block
        }

    A try block starts with the keyword try, followed by an opening brace and a closing brace.
    The code for the try block is placed inside the opening and the closing braces.

    A try block cannot be used just by itself.

    It must be followed by one or more catch blocks, or one finally block, or a combination of both.

    To handle an exception that might be thrown inside a try block, use a catch block.

    One catch block can be used to handle multiple types of exceptions.

    The syntax for a catch block is similar to the syntax for a method.

        catch ( ExceptionClassName parameterName ) {
            // Exception handling  code
        }

    A catch block's declaration is exactly like a method declaration.

    It starts with the keyword catch, followed by a pair of parentheses.
    Within the parentheses, it declares a parameter.

    The parameter type is the name of the exception class that it is supposed to catch.

    The parameterName is a user-given name.
    Parentheses are followed by an opening brace and a closing brace.
    The exception handling code is placed within the braces.

    When an exception is thrown, the reference of the exception object is copied to the parameterName.
    We can use the parameterName to get information from the exception object.

    We can associate one or more catch blocks to a try block.
    The general syntax for a try-catch block is as follows.

        try  {
            // Your code  that may throw  an  exception
        }
        catch ( ExceptionClass1 e1 ) {
            // Handle exception of ExceptionClass1 type
        }
        catch ( ExceptionClass2 e2 ) {
            // Handle exception of ExceptionClass2 type
        }
        catch ( ExceptionClass3 e3 ) {
            // Handle exception of ExceptionClass3 type
        }
 */

public class ExceptionHandling
{
    // The following code shows how to handle divide by zero exception.
    public static void Test() {

        int x = 10, y = 0, z;

        try {
            z = x / y;
            System.out.println( "z = " + z );
        }
        catch ( ArithmeticException e ) {

            String msg = e.getMessage();
            System.out.println( "The error is: " + msg );
        }

        System.out.println( "The end." );
    }
    // The code above generates the following result.
        // The error is: / by zero
        // The end
}
