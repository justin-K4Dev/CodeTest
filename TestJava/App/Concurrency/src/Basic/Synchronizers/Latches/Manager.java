/**
 * Created by justin on 2015-07-08.
 */

package Basic.Synchronizers.Latches;

import java.util.concurrent.CountDownLatch;

public class Manager extends Thread
{
    private CountDownLatch latch;

    public Manager( CountDownLatch latch ) {
        this.latch = latch;
    }

    @Override
    public void run() {
        try {
            System.out.println( "waiting for services to start." );
            latch.await();
            System.out.println( "started." );
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
