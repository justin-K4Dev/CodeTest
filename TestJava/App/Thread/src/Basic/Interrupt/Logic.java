package Basic.Interrupt;

/**
 * Created by justin on 2015-06-30.
 */
public class Logic
{
    public static void TestInterrupt() {

        // Example 1
        {
            System.out.println( "Example 1" );
            System.out.println( "#1: " + Thread.interrupted() );

            // Now interrupt the main thread
            Thread.currentThread().interrupt();

            // Check if it has been interrupted
            System.out.println( "#2: " + Thread.interrupted() );

            // Check again if it has been interrupted
            System.out.println( "#3: " + Thread.interrupted() );
        }

        // Example 2
        {
            System.out.println( "Example 2" );
            Thread t = new Thread( Logic::UpdateCounter1 );
            t.start();
            try {
                Thread.currentThread().sleep( 1000 );
            }
            catch ( InterruptedException e ) {
                e.printStackTrace();
            }
            t.interrupt();
        }

        // Example 3
        {
            System.out.println( "Example 3" );

            System.out.println( "#1: " + Thread.interrupted() );
            Thread t = Thread.currentThread();
            t.interrupt();

            System.out.println( "#2: " + t.isInterrupted() );
            System.out.println( "#3: " + t.isInterrupted() );
            System.out.println( "#4: " + Thread.interrupted());
            System.out.println( "#5: " + t.isInterrupted());
        }

        // Example 4
        {
            System.out.println( "Example 4" );
            Thread t = new Thread( Logic::UpdateCounter2 );
            t.start();
            try {
                Thread.sleep( 1000 );
            }
            catch ( InterruptedException e ) {
                System.out.println( "I got interrupted !" );
            }
            t.interrupt();
        }
    }

    public static void UpdateCounter1() {

        int counter = 0;
        while ( !Thread.interrupted() ) {
            counter++;
        }
        System.out.println( "Counter:" + counter );
    }

    public static void UpdateCounter2() {

        int counter = 1;
        while ( true ) {
            try {
                Thread.sleep( 1000 );
                System.out.println( "Counter: " + counter++ );
            }
            catch ( InterruptedException e ) {
                System.out.println( "I got interrupted !" );
            }
        }
    }
}
