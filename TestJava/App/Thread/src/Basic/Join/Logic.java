/**
 * Created by justin on 2015-06-29.
 */

package Basic.Join;

public class Logic {

    public static void TestJoin() {

        {
            System.out.println( "No join Thread !!!" );

            Thread t = new Thread( Logic::Print );
            t.start();
            System.out.println( "Done" );
        }

        {
            System.out.println( "Join Thread !!!" );

            Thread t = new Thread( Logic::Print );
            t.start();
            try {
                // The following code uses join() to wait for the thread to finish then print "Done"
                t.join();
            }
            catch ( InterruptedException e ) {
                e.printStackTrace();
            }
            System.out.println( "Done" );
        }
    }

    public static void Print() {

        for ( int i = 1; i <= 5; i++ ) {
            try {
                System.out.println( "Counter: " + i );
                Thread.sleep( 1000 );
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
