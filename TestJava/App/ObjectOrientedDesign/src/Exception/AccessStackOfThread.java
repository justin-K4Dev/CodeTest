package Exception;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Accessing the Stack of a Thread

    The following code shows how to get to the stack frames of a thread.
    A Throwable object captures the stack of the thread at the point it is created.
 */

public class AccessStackOfThread
{
    public static void Test() {
        Method1();
    }
    // The code above generates the following result.
        // Frame count: 4
        // Frame Index: 0
        // File Name: AccessStackOfThread.java
        // Class Name: AccessStackOfThread
        // Method Name: Method3
        // Line Number: 35
        // Frame Index: 1
        // File Name: AccessStackOfThread.java
        // Class Name: AccessStackOfThread
        // Method Name: Method2
        // Line Number: 36

    public static void Method1() {
        Method2();
    }

    public static void Method2() {
        Method3();
    }

    public static void Method3() {

        Throwable t = new Throwable();
        StackTraceElement[] frames = t.getStackTrace();
        PrintStackDetails( frames );
    }

    public static void PrintStackDetails( StackTraceElement[] frames ) {

        System.out.println( "Frame count: " + frames.length );

        for ( int i = 0; i < frames.length; i++ ) {

            int frameIndex = i; // i = 0 means top frame

            System.out.println( "Frame Index: " + frameIndex );
            System.out.println( "File Name: " + frames[i].getFileName() );
            System.out.println( "Class Name: " + frames[i].getClassName() );
            System.out.println( "Method Name: " + frames[i].getMethodName() );
            System.out.println( "Line Number: " + frames[i].getLineNumber() );
        }
    }

}
