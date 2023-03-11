/**
 * Created by justin on 2015-07-07.
 */

package Basic.Synchronizers.Phasers;

import java.util.Random;
import java.util.concurrent.Phaser;

public class StartTask extends Thread
{
    private Phaser phaser;
    private String taskName;
    private static Random rand = new Random();

    public StartTask(String taskName, Phaser phaser) {
        this.taskName = taskName;
        this.phaser = phaser;
    }

    @Override
    public void run() {

        System.out.println( taskName + ":Initializing..." );
        int sleepTime = rand.nextInt( 5 ) + 1;
        try {
            Thread.sleep( sleepTime * 1000 );
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println( taskName + ":Initialized..." );
        phaser.arriveAndAwaitAdvance();
        System.out.println( taskName + ":Started..." );
    }
}
