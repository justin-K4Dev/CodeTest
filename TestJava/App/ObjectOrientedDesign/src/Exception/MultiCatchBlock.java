package Exception;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Multi-Catch Block

    Java 7 added support for a multi-catch block to handle multiple types of exceptions in a catch block.

    We can specify multiple exceptions types in a multi-catch block.
    Multiple exceptions are separated by a vertical bar (|).

    To catch three exceptions: Exception1, Exception2, and Exception3.

        try  {
            // May throw Exception1, Exception2, or Exception3
        }
        catch ( Exception1 | Exception2 | Exception3 e ) {
            // Handle  Exception1, Exception2, and Exception3
        }

    In a multi-catch block, it is not allowed to have alternative exceptions that are related by subclassing.

    For example, the following multi-catch block is not allowed,
    because Exception1 and Exception2 are subclasses of Throwable:

        try  {
            // May  throw  Exception1, Exception2, or  Exception3
        }
        catch ( Exception1 | Exception2 | Throwable e ) {
            // Handle  Exceptions here
        }
 */

class Exception1 extends Exception
{
    public Exception1() {
        super();
    }

    public Exception1( String message ) {
        super( message );
    }

    public Exception1( String message, Throwable cause ) {
        super( message, cause );
    }

    public Exception1( Throwable cause ) {
        super( cause );
    }
}

class Exception2 extends Exception
{
    public Exception2() {
        super();
    }

    public Exception2( String message ) {
        super( message );
    }

    public Exception2( String message, Throwable cause ) {
        super( message, cause );
    }

    public Exception2( Throwable cause ) {
        super( cause );
    }
}

class Exception3 extends Exception
{
    public Exception3() {
        super();
    }

    public Exception3( String message ) {
        super( message );
    }

    public Exception3( String message, Throwable cause ) {
        super( message, cause );
    }

    public Exception3( Throwable cause ) {
        super( cause );
    }
}

public class MultiCatchBlock
{
    public static void Test() {

        int i = 0;

        try  {
            if( 0 > i ) {
                throw new Exception1();
            }
            else if( 0 == i ) {
                throw new Exception2();
            }
            else {
                throw new Exception3();
            }
        }
        catch ( Exception1 | Exception2 | Exception3 e ) {
            e.printStackTrace();
        }
    }
}