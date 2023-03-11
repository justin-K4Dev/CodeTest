/**
 * Created by justin on 2015-07-04.
 */

package Basic.AtomicVariable;

import java.util.concurrent.atomic.AtomicLong;

public class Worker extends Thread
{
    private AtomicLong value = new AtomicLong( 0L );

    public long Increment() {
        return value.incrementAndGet();
    }

    public long Decrement() {
        return value.decrementAndGet();
    }

    @Override
    public void run() {

        for( int i = 0; i < 20; i++ ) {
            try { Thread.sleep( 1000 ); }
            catch ( InterruptedException e ) { e.printStackTrace(); }
            long value = this.Increment();
            System.out.println( "IncValue: " + value );
        }
    }
}
