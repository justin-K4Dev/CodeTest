/**
 * Created by justin on 2015-07-13.
 */

package Basic.Executor;

import java.util.concurrent.Callable;

public class CallableTask implements Callable<Integer>
{
    private int taskId;

    public CallableTask( int taskId ) {
        this.taskId = taskId;
    }

    @Override
    public Integer call() throws InterruptedException {

        int sleepSec = 1;
        try {
            System.out.println( "Task #" + this.taskId );
            Thread.sleep( sleepSec * 1000 );
        }
        catch ( InterruptedException e ) {
            System.out.println( "Task #" + this.taskId + " has been interupted." );
            throw e;
        }

        return sleepSec;
    }
}
