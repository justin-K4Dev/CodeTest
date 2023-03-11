package Exception;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Finally block

    A try block can also have zero or one finally block.
    A finally block is always used with a try block.


    Syntax

    The syntax for using a finally block is

        finally {
            // Code for finally block
        }

    A finally block starts with the keyword finally, which is followed by an opening brace and a closing brace.
    The code for a finally block is placed inside the braces.

    There are two possible combinations of try, catch, and finally blocks: try-catch-finally or try-finally.
    A try block may be followed by zero or more catch blocks.
    A try block can have a maximum of one finally block.
    A try block must have either a catch block, a finally block, or both.

    The syntax for a try-catch-finally block is

        try  {
            // Code for try block
        }
        catch( Exception1 e1 )  {
            // Code for catch block
        }
        finally  {
            // Code for finally block
        }

    The syntax for a try-finally block is

        try  {
            // Code for try block
        }
        finally  {
            // Code for finally block
        }

    A finally block is guaranteed to be executed no matter what happens in the associated try and/or catch block.
    Typically, we use a finally block to write cleanup code.

    For example, we may obtain some resources that must be released when we are done with them.
    A try-finally block lets you implement this logic.

    Your code structure would look as follows:

        try  {
            // Obtain and use some resources here
        }
        finally  {
            // Release the resources that were obtained in the try block
        }


    Rethrowing an Exception

    An exception that is caught can be rethrown.
 */

class RethrowException extends Exception
{
    public RethrowException() {
        super();
    }

    public RethrowException( String message ) {
        super( message );
    }

    public RethrowException( String message, Throwable cause ) {
        super( message, cause );
    }

    public RethrowException( Throwable cause ) {
        super( cause );
    }
}

public class FinallyBlock
{
    public static void Test1() {

        int x = 10, y = 0, z = 0;

        try {
            System.out.println( "Before dividing x by y." );
            z = x / y;
            System.out.println( "After dividing x by y." );
        }
        catch ( ArithmeticException e ) {
            System.out.println( "Inside catch block a." );
        }
        finally {
            System.out.println( "Inside finally block a." );
        }

        try {
            System.out.println( "Before setting z to 2." );
            z = 2;
            System.out.println( "After setting z to 2." );
        }
        catch ( Exception e ) {
            System.out.println( "Inside catch block b." );
        }
        finally {
            System.out.println( "Inside finally block b." );
        }

        try {
            System.out.println( "Inside try block c." );
        }
        finally {
            System.out.println( "Inside finally block c." );
        }

        try {
            System.out.println( "Before executing System.exit()." );
            System.exit( 0 );
            System.out.println( "After executing System.exit()." );
        }
        finally {
            // This finally block will not be executed
            // because application exits in try block
            System.out.println( "Inside finally block d." );
        }
    }
    // The code above generates the following result.
        // Before diving x by y.
        // Inside catch block a.
        // Inside finally block a.
        // Before setting z to 2.
        // After setting z to 2.
        // Inside finally block b.
        // Inside try block c.
        // Inside finally block c.
        // Before executing System exit().


    public static void Method1() throws RethrowException {
        try {
            Method2();
        }
        catch ( RethrowException e ) {
            e.fillInStackTrace();
            throw e;
        }
    }

    public static void Method2() throws RethrowException {
        throw new RethrowException( "An error has occurred." );
    }

    public static void Test2() {

        try {
            Method1();
        }
        catch ( RethrowException e ) {
            // Print the stack trace
            e.printStackTrace();
        }
    }
    // The code above generates the following result.
        // RethrowException: An error has occurred.
        // at FinallyBlock.Method1(FinallyBlock.java:151)
        // at FinallyBlock.Test2(FinallyBlock.java:165)
        // at ...
}


