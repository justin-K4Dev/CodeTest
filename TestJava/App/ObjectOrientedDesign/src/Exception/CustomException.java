package Exception;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Custom Exception

    We can create our own exception classes.
    They must extend an existing exception class.

        <Class Modifiers> class <Class Name> extends <Exception Class Name>
        {
        }
        <Class Name> is the exception class name.

    To create a MyException class, which extends the java.lang.Exception class.


    Syntax

    The syntax would be as follows:
        public class MyException extends Exception
        {
        }

    An exception class is like any other classes in Java.
    Typically, we do not add any methods to our exception class.
    Many useful methods that can be used to query an exception object's state are declared in the Throwable class.


    Custom Exception Class Constructors

    Typically, we include four constructors to our exception class.
    All constructors will call the corresponding constructor of its superclass using the super keyword.

        class MyException extends Exception
        {
            public MyException() {
                super();
            }

            public MyException( String message ) {
                super( message );
            }

            public MyException( String message, Throwable cause ) {
                super( message, cause );
            }

            public MyException( Throwable cause ) {
                super(cause);
            }
        }

    The first constructor creates an exception with null as its detailed message.

    The second constructor creates an exception with a detailed message.

    The third and fourth constructors let you create an exception by wrapping
    another exception with/without a detailed message.

    You can throw an exception of type MyException.

        throw new MyException( "Your message goes here" );

    We can use the MyException class in a throws clause in a method/constructor declaration
    or as a parameter type in a catch block.

        public void m1() throws MyException {
        }

    or catch MyException class

        try {
        }
        catch( MyException e ) {
        }


    Throwable

    The following list shows some of the commonly used methods of the Throwable class.
    Throwable class is the superclass of all exception classes in Java.
    All of the methods shown in this table are available in all exception classes.

        * Throwable getCause()
          returns the cause of the exception. If the cause of the exception is not set, it returns null.
        * String getMessage()
          returns the detailed message of the exception.
        * StackTraceElement[] getStackTrace()
          returns an array of stack trace elements.
        * Throwable initCause(Throwable cause)
          sets the cause of an exception.
          There are two ways to set an exception as the cause of an exception.
          Other way is to use the constructor, which accepts the cause as a parameter.
        * void printStackTrace()
          prints the stack trace on the standard error stream.
        * void printStackTrace(PrintStream s)
          prints the stack trace to the specified PrintStream object.
        * void printStackTrace(PrintWriter s)
          prints the stack trace to the specified PrintWriter object.
        * String toString()
          returns a short description of the exception object.
 */

import java.io.PrintWriter;
import java.io.StringWriter;

class MyException extends Exception
{
    public MyException() {
        super();
    }

    public MyException( String message ) {
        super( message );
    }

    public MyException( String message, Throwable cause ) {
        super( message, cause );
    }

    public MyException( Throwable cause ) {
        super( cause );
    }
}


public class CustomException
{
    // The following code demonstrates the use of the printStackTrace() method for an exception class.
    public static void Test1() {

        try  {
            Method2();
        }
        catch( MyException e )  {
            e.printStackTrace();
        }
    }
    // The code above generates the following result.
        // MyException: Your message goes here
        // at CustomException.Method1() (CustomException:161)
        // at CustomException.Method2() (CustomException:166)
        // at CustomException.Test1() (CustomException:134)
        // at ...

    public static void Test2() {

        try  {
            Method2();
        }
        catch( MyException e )  {
            String str = GetStackTrace( e );
            System.out.println( str );
        }
    }
    // The code above generates the following result.
        // MyException: Your message goes here
        // at CustomException.Method1() (CustomException:161)
        // at CustomException.Method2() (CustomException:166)
        // at CustomException.Test2() (CustomException:150)
        // at ...

    public static void Method1() throws MyException {
        // You can throw an exception of type MyException.
        throw new MyException( "Your message goes here" );
    }

    public static void Method2() throws MyException {
        Method1();
    }

    public static String GetStackTrace( Throwable e ) {

        StringWriter strWriter = new StringWriter();
        PrintWriter printWriter = new PrintWriter( strWriter );
        e.printStackTrace( printWriter );

        // Get the stack trace as a string
        String str = strWriter.toString();

        return str;
    }
}