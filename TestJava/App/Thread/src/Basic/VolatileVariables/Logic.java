/**
 * Created by justin on 2015-06-30.
 */

package Basic.VolatileVariables;

public class Logic
{
    public static void TestVolatileVariables() {

        Worker ts = new Worker();

        ts.start();
        try {
            Thread.sleep( 3000 );
        }
        catch ( InterruptedException e ) {
            e.printStackTrace();
        }

        System.out.println( "Going to set the stop flag to true" );
        ts.StopThread();
    }
}
