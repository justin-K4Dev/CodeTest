/**
 * Created by justin on 2015-07-07.
 */

package Basic.Synchronizers.Semaphores;

import java.util.Random;

public class Guest extends Thread
{
    private Restaurant r;
    private int guestID;
    private static final Random random = new Random();

    public Guest ( Restaurant r, int guestID ) {
        this.r = r;
        this.guestID = guestID;
    }

    @Override
    public void run() {

        r.GetTable( this.guestID ); // Get a table

        try {
            int eatingTime = random.nextInt( 30 ) + 1;
            System.out.println( "Guest #" + this.guestID + " will eat for " + eatingTime + " seconds." );
            Thread.sleep( eatingTime * 1000 );
            System.out.println( "Guest #" + this.guestID + " is done eating." );
        }
        catch ( InterruptedException e ) {
            e.printStackTrace();
        }
        finally {
            r.ReturnTable( this.guestID );
        }
    }
}
