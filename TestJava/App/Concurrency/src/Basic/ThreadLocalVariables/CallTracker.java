/**
 * Created by justin on 2015-07-13.
 */

package Basic.ThreadLocalVariables;

public class CallTracker
{
    private static ThreadLocal<Integer> threadLocal = new ThreadLocal<Integer>();

    public static void Do() {

        int counter = 0;
        Integer counterObject = threadLocal.get();

        if ( counterObject == null ) {
            counter = 1;
        }
        else {
            counter = counterObject.intValue();
            counter++;
        }

        threadLocal.set( counter );
        String threadName = Thread.currentThread().getName();

        System.out.println( "Call counter for " + threadName + " = " + counter );
    }
}
