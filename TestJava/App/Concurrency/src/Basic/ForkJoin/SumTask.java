/**
 * Created by justin on 2015-07-13.
 */

package Basic.ForkJoin;

import java.util.concurrent.RecursiveTask;
import java.util.List;
import java.util.ArrayList;

public class SumTask extends RecursiveTask<Long>
{
    private int count;

    public SumTask( int count ) {
        this.count = count;
    }

    @Override
    protected Long compute() {

        long result = 0;

        if ( this.count <= 0 ) {
            return 0L;
        }
        else if ( this.count == 1 ) {
            return (long) this.GetRandomInteger();
        }

        List<RecursiveTask<Long>> forks = new ArrayList<>();
        for ( int i = 0; i < this.count; i++ ) {
            SumTask subTask = new SumTask( 1 );
            subTask.fork();
            forks.add( subTask );
        }

        // all subtasks finish and combine the result
        for ( RecursiveTask<Long> subTask : forks ) {
            result = result + subTask.join();
        }

        return result;
    }

    public int GetRandomInteger() { return 2; }
}
