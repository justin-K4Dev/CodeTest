/**
 * Created by justin on 2015-07-08.
 */

package Basic.Synchronizers.Latches;

import java.util.concurrent.CountDownLatch;

public class Helper extends Thread
{
    private int ID;
    private CountDownLatch latch;

    public Helper( int ID, CountDownLatch latch ) {
        this.ID = ID;
        this.latch = latch;
    }

    @Override
    public void run() {
        try {
            Thread.sleep(1000);
            System.out.println( "Service #" + ID + " has  started..." );
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
        finally {
            this.latch.countDown();
        }
    }
}
