package Object;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Object Finalize

    Java provides a way to perform resource release, when an object is about to be destroyed.

    In Java, we create objects, but we cannot destroy objects.

    The JVM runs a low priority special task called garbage collector to destroy all objects
    that are no longer referenced.

    The garbage collector gives us a chance to execute the cleanup code before an object is destroyed.

    The Object class has a finalize() method, which is declared as follows:

        protected void finalize() throws Throwable  {  }

    The finalize() method in the Object class does not do anything.

    You need to override the method in your class.

    The finalize() method of your class will be called by the garbage collector
    before an object of your class is destroyed.
 */

class Finalize
{
    private int x;

    public Finalize( int x ) {
        this.x = x;
    }

    public void finalize() {
        System.out.println( "Finalizing " + this.x );
    }
}


public class ObjectFinalize
{
    public static void Test() {

        for ( int i = 0; i < 20000; i++ ) {
            new Finalize( i );
        }
    }
    // The code above generates the following result.
        // ...
        // Finalizing 10040
        // Finalizing 10039
        // Finalizing 10038
        // ...
}
