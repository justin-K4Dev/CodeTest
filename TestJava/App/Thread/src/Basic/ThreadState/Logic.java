/**
 * Created by justin on 2015-06-30.
 */

package Basic.ThreadState;

public class Logic
{
    public static void TestThreadState() {

        Worker ts = new Worker();

        ts.start();

        try { Thread.sleep( 2000 ); }
        catch ( InterruptedException e ) { e.printStackTrace(); }
        ts.SuspendThread();

        try { Thread.sleep( 2000 ); }
        catch ( InterruptedException e ) { e.printStackTrace(); }
        ts.ResumeThread();

        try { Thread.sleep( 2000 ); }
        catch ( InterruptedException e ) { e.printStackTrace(); }
        ts.StopThread();
    }
}
