package Exception;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Exception Class Hierarchy

    The exception class hierarchy starts at the java.lang.Throwable class.

    When an exception is thrown, it must be an object of the Throwable class, or any of its subclasses.

    The parameter of the catch block must be of type Throwable, or one of its subclasses,
    such as Exception, ArithmeticException, IOException, etc.

    We can create our own exception classes by inheriting our classes from one of the exception classes.


    Arranging Multiple catch Blocks

    Java runtime selects the appropriate catch block
    and starts looking for the appropriate catch clock sequentially starting from the first catch block.

    Multiple catch blocks for a try block must be arranged from
    the most specific exception type to the most generic exception type.

    The following code uses a valid sequence of multiple catch blocks.

    The ArithmeticException class is a subclass of the RuntimeException class.

    If both of these exceptions are handled in catch blocks for the same try block, the most specific type,
    which is ArithmeticException, must appear before the most generic type, which is RuntimeException.

        try  {
            // Do  something, which  might  throw  Exception
        }
        catch( ArithmeticException e1 )  {
            // Handle  ArithmeticException first
        }
        catch( RuntimeException e2 )  {
            // Handle  RuntimeException after  ArithmeticException
        }


    Checked and Unchecked Exceptions

    There are three types of exceptions

        * There are some exceptions that have a higher potential to occur.
          We can handle them in a try-catch block.
          Or we can specify in the calling method/constructor declaration that it may throw an exception.

        * Error are the exceptions that may occur, and there is little we can do to handle it.
          For example, java.lang.OutOfMemeoryError. We cannot do anything to recover from an out of memory error.
          Classes in the exception class hierarchy, which are subclasses of the Error class,
          and the Error class itself, fall into this category of exception.
          The compiler does not insist on taking an action on our code.
          If an exception of this kind is thrown at runtime,
          the runtime will handle it for you by displaying a detailed error message and halting the application.

        * There are exceptions that may occur at runtime, and we may recover from the exceptional condition.
          Classes in the exception class hierarchy, which are subclasses of the RuntimeException class,
          and the RuntimeException class itself, fall into this category.
          The compiler does not insist on taking an action on our code.

    Exceptions in the first category are known as checked exceptions
    because the compiler checks that they are handled in the code.

    The Throwable class, the Exception class, and subclasses of the Exception class,
    excluding the RuntimeException class and its subclasses, are called checked exceptions.

    All exceptions that are not checked exceptions are called unchecked exceptions
    because the compiler does not check if they are handled in the code.

    The Error class, all subclasses of the Error class, the RuntimeException class,
    and all its subclasses are unchecked exceptions.

    We can handle the unchecked exception if we want to, the compiler would not force us to do it.
    The program structure for handling a checked or an unchecked exception is the same.

    The following code shows how to handle a checked exception

        import java.io.IOException;

        public class Main
        {
            public static void main( String[] argv ) {

                try {
                    int input = System.in.read();
                    if ( input != -1 ) {
                        System.out.println( input );
                    }
                }
                catch ( IOException e ) {
                    System.out.print( "IOException occurred." );
                }
            }
        }
 */

import java.io.IOException;

public class ExceptionClass
{
    public static void Test() {

        try {
            int input = System.in.read();
            if ( input != -1 ) {
                System.out.println(input);
            }
        }
        catch ( IOException e ) {
            System.out.print( "IOException occurred." );
        }
    }
}
