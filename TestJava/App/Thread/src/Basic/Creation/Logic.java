/**
 * Created by justin on 2015-06-28.
 */

package Basic.Creation;

public class Logic {

    public static void TestMethod() {
        Thread newThread = new Thread( Logic::Execute );
        newThread.start();
    }

    public static void TestRunnable() {

        // use Lambda
        Runnable newRunnable = () -> System.out.println( "Call Runnable Lambda !!!" );

        Thread newThread = new Thread( newRunnable );
        newThread.start();
    }

    public static void TestWorkerThread() {

        Worker worker = new Worker();
        worker.start();
    }

    public static void TestThread() {

        Thread newThread = new Thread();
        newThread.start();
    }

    public static void Execute() {
        System.out.println( "Call Logic::Execute() !!!" );
    }
}
