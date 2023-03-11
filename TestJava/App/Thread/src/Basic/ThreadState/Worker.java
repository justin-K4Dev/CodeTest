/**
 * Created by justin on 2015-06-30.
 */

package Basic.ThreadState;

public class Worker extends Thread
{
    private volatile boolean keepRunning = true;
    private boolean suspended = false;

    public synchronized void StopThread() {
        this.keepRunning = false;
        this.notify();
    }

    public synchronized void SuspendThread() {
        this.suspended = true;
    }

    public synchronized void ResumeThread() {
        this.suspended = false;
        this.notify();
    }

    @Override
    public void run() {
        System.out.println( "Thread started !!!" );

        while ( keepRunning ) {
            try {
                System.out.println( "Going to sleep..." );
                Thread.sleep( 1000 );

                synchronized ( this ) {
                    while ( suspended ) {
                        System.out.println( "Suspended..." );
                        this.wait();
                        System.out.println( "Resumed..." );
                    }
                }
            }
            catch ( InterruptedException e ) {
                e.printStackTrace();
            }
        }
    }
}
