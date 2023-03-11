/**
 * Created by justin on 2015-07-13.
 */

package Basic.Executor;

import java.util.concurrent.Callable;

class SleepingTask implements Callable<Result>
{
    private int taskId;
    private int loopCounter;

    public SleepingTask( int taskId, int loopCounter ) {

        this.taskId = taskId;
        this.loopCounter = loopCounter;
    }

    @Override
    public Result call() throws InterruptedException {

        int sleepSec = 1;
        int totalSleepTime = 0;

        for (int i = 1; i <= loopCounter; i++) {
            try {
                System.out.println( "Task #" + this.taskId + " - Iteration #" + i );
                Thread.sleep( sleepSec );
                totalSleepTime = totalSleepTime + sleepSec;
            }
            catch (InterruptedException e) {
                System.out.println( "Task #" + this.taskId + " has been interupted." );
                throw e;
            }
        }

        return new Result( taskId, totalSleepTime );
    }
}