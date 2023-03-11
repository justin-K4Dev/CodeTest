/**
 * Created by justin on 2015-06-29.
 */

package Basic.MultipleThreads;

public class Logic {

    private static int value = 1;

    public static void TestNotify() {

        Thread newThread;

        newThread = new Thread( () -> {
            while ( true ) {
                UpdateValue();
            }
        } );
        newThread.start();

        newThread = new Thread( () -> {
            while ( true ) {
                MonitorValue();
            }
        } );
        newThread.start();
    }

    public static synchronized void UpdateValue() {
        System.out.println( "start:" + value );
        value = value + 1;
        value = value - 1;
        System.out.println( "end:" + value );
    }

    public static synchronized void MonitorValue() {
        int b = value;
        if ( b != 1 ) {
            System.out.println( "Value changed: " + b );
            System.exit( 1 );
        }
    }

    public synchronized void TestSynchronized1() {
        // Method code goes here
        // To declare a method as a critical section
    }

    public static synchronized void TestSynchronized2() {
        // Method code goes here
        // To declare a method as a critical section
    }

    public void TestSynchronized3() {
        synchronized (this) {
            // only one thread can execute here at a time
        }
    }

    public void TestSynchronized4() {
        synchronized ( Logic.class ) {
            // only one thread can execute here at a time
        }
    }

    public static void TestMultipleThread() {

        Thread newThread1 = new Thread( Logic::Print );
        Thread newThread2 = new Thread( Logic::Print );

        newThread1.start();
        newThread2.start();
    }

    public static void Print() {

        for ( int i = 1; i <= 500; i++ ) {
            System.out.println( i );
        }
    }
}
