/**
 * Created by justin on 2015-07-13.
 */

package Basic.ForkJoin;

import java.util.concurrent.ForkJoinPool;

public class Logic
{
    public static void TestForkJoin() {

        ForkJoinPool pool = new ForkJoinPool();
        SumTask task = new SumTask( 3 );
        long sum = pool.invoke( task );

        System.out.println( "Sum is " + sum );
    }
}
