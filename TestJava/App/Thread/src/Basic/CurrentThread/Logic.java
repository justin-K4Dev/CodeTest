/**
 * Created by justin on 2015-06-29.
 */

package Basic.CurrentThread;

public class Logic {

    public static void TestException() {

        CatchAllThreadExceptionHandler handler = new CatchAllThreadExceptionHandler();

        // Set an uncaught exception handler for main thread
        Thread.currentThread().setUncaughtExceptionHandler( handler );

        // Throw an exception
        throw new RuntimeException();
    }

    public static void TestCurrentThread() {

        Worker ct1 = new Worker( "First Thread" );
        Worker ct2 = new Worker( "Second Thread" );
        ct1.start();
        ct2.start();

        Thread t = Thread.currentThread();
        String threadName = t.getName();
        System.out.println( "Call Logic::TestCurrentThread() - Thread name: " + threadName );
    }
}
