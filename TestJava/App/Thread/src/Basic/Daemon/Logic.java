package Basic.Daemon;

/**
 * Created by justin on 2015-06-30.
 */
public class Logic
{
    public static void TestDaemon() {

        Thread t = new Thread( Logic::PrintDaemon );
        t.setDaemon( false );
        t.start();

        System.out.println( "Exiting main method !!!" );
    }

    public static void PrintDaemon() {

        int counter = 1;

        while ( true ) {
            try {
                System.out.println( "Counter: " + counter++ );
                Thread.sleep( 2000 );
            }
            catch ( InterruptedException e ) {
                e.printStackTrace();
            }
        }
    }
}
