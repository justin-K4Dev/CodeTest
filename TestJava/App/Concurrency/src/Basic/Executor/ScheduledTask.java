/**
 * Created by justin on 2015-07-13.
 */

package Basic.Executor;

import java.time.LocalDateTime;

public class ScheduledTask implements Runnable
{
    private int taskId;

    public ScheduledTask( int taskId ) {
        this.taskId = taskId;
    }

    @Override
    public void run() {

        LocalDateTime currentDateTime = LocalDateTime.now();
        System.out.println( "Task #" + this.taskId + " ran at " + currentDateTime );
    }
}
