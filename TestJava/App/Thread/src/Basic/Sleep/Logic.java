/**
 * Created by justin on 2015-06-29.
 */

package Basic.Sleep;

public class Logic {

    public static void TestSleep() {
        try {
            System.out.println( "Sleep for 5 seconds" );
            Thread.sleep( 5000 );
            // TimeUnit.SECONDS.sleep( 5 );
            System.out.println( "Woke up" );
        }
        catch ( InterruptedException e ) {
            System.out.println( "Interrupted" );
        }
        System.out.println( "Done" );
    }
}
