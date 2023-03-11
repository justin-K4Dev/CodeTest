/**
 * Created by justin on 2015-07-08.
 */

package Basic.Synchronizers.Phasers;

import java.util.List;
import java.util.concurrent.Phaser;

public class AdderTask extends Thread
{
    private Phaser phaser;
    private String taskName;
    private List<Integer> list;

    public AdderTask(String taskName, Phaser phaser, List<Integer> list) {
        this.taskName = taskName;
        this.phaser = phaser;
        this.list = list;
    }

    @Override
    public void run() {

        do {
            System.out.println( taskName + " added " + 3 );
            list.add( 3 );
            phaser.arriveAndAwaitAdvance();
        }
        while ( !phaser.isTerminated() );
    }
}
