package Basic.VolatileVariables;

/**
 * Created by justin on 2015-06-30.
 */
public class Worker extends Thread
{
    private boolean keepRunning = true;

    @Override
    public void run() {
        System.out.println( "Thread started" );

        while ( keepRunning ) {
            try {
                System.out.println( "Going to sleep" );
                Thread.sleep( 1000 );
            }
            catch ( InterruptedException e ) {
                e.printStackTrace();
            }
        }

        System.out.println( "Thread stopped" );
    }

    public void StopThread() {
        this.keepRunning = false;
    }
}
