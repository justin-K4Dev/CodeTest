package Basic.LeftCycle;

/**
 * Created by justin on 2015-06-30.
 */
public class Worker extends Thread
{
    private volatile boolean keepRunning = true;
    private boolean wait = false;
    private Object syncObject = null;

    public Worker( Object syncObject ) {
        this.syncObject = syncObject;
    }

    @Override
    public void run() {
        System.out.println( "Thread started" );

        while ( keepRunning ) {
            synchronized ( syncObject ) {
                if ( wait ) {
                    try {
                        syncObject.wait();
                    }
                    catch ( InterruptedException e ) {
                        e.printStackTrace();
                    }
                }
            }
        }
        System.out.println( "Thread stopped" );
    }

    public void SetKeepRunning ( boolean keepRunning ) {
        this.keepRunning = keepRunning;
    }

    public void SetWait ( boolean wait ) {
        this.wait = wait;
    }
}
