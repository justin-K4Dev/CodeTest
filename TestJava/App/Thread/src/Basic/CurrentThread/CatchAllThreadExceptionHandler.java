/**
 * Created by justin on 2015-06-29.
 */

package Basic.CurrentThread;

public class CatchAllThreadExceptionHandler implements Thread.UncaughtExceptionHandler
{
    public void uncaughtException( Thread t, Throwable e ) {
        System.out.println( "Caught exception from Thread: " + t.getName() );
    }
}