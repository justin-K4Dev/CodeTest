package Basic.CurrentThread;

/**
 * Created by justin on 2015-06-29.
 */

public class Worker extends Thread
{
    public Worker( String name ) {
        super( name );
    }

    @Override
    public void run() {
        System.out.println( "Call Worker::run() !!!" );

        Thread t = Thread.currentThread();
        String threadName = t.getName();
        System.out.println( "Thread name: " + threadName );
    }
}