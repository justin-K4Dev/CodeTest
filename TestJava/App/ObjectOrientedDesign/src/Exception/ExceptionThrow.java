package Exception;

/**
 * Created by justin on 2015-07-18.
 */

/*
    Exception Throw

    If a piece of code may throw a checked exception, we have two options:

        * Handle the checked exception with a try-catch block.
        * Specify in your method/constructor declaration with throws clause.

    Syntax

    The general syntax for a throws clause is

        <modifiers> <return type> <method name>(<params>) throws<List of Exceptions> {
        }

    The keyword throws is used to specify a throws clause.
    The throws clause is placed after the closing parenthesis of the method's parameters list.

    The throws keyword is followed by a comma-separated list of exception types.

    Throwing an Exception

    We can throw an exception in our code using a throw statement.
    The syntax for a throw statement is

        throw <A throwable object reference>;

    throw is a keyword, which is followed by a reference to a throwable object.
    A throwable object is an instance of a class, which is a subclass of the Throwable class,
    or the Throwable class itself.

    If we throw a checked exception, we must handle it with a try-catch block,
    or using a throws clause in the method or constructor declaration.
    These rules do not apply if you throw an unchecked exception.
 */

import java.io.IOException;

public class ExceptionThrow {

    // Here is the code showing how to use it.
    public static void Test1() {
        try {
            ReadChar();
        }
        catch (IOException e) {
            System.out.println( "Error occurred." );
        }
    }
    // The code above generates the following result.
    // -1

    // We can continue to throw exception.
    public static void Test2() throws IOException {
        ReadChar();
    }
    // The code above generates the following result.
    // -1

    // The following is an example of a throw statement, which throws an IOException:
    public static void Test3() throws IOException {

        // Create an object of IOException
        IOException e1 = new IOException( "File not found" );

        // Throw the IOException
        throw  e1;
    }

    // We can create a throwable object and throw it in one statement.
    public static void Test4() throws IOException {

        // Throw an IOException
        throw new IOException( "File not found" );
    }

    // The following code shows how to use a throws Clause in a Method's Declaration
    public static void ReadChar() throws IOException {
        int input = System.in.read();
        System.out.println( input );
    }
}
