/**
 * Created by justin on 2015-07-09.
 */

package Basic.Executor;

public class RunnableTask implements Runnable
{
    private int taskId;
    private int loopCounter;

    public RunnableTask( int taskId, int loopCounter ) {
        this.taskId = taskId;
        this.loopCounter = loopCounter;
    }

    @Override
    public void run() {

        for ( int i = 1; i <= loopCounter; i++ ) {
            try {
                System.out.println( "Task #" + this.taskId + " - Iteration #" + i );
                Thread.sleep( 1000 );
            }
            catch ( Exception e ) {
                System.out.println( "Task #" + this.taskId + " has been interrupted." );
                break;
            }
        }
    }
}
