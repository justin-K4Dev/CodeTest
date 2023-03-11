/**
 * Created by justin on 2015-07-08.
 */

package Basic.Synchronizers.Exchangers;

import java.util.ArrayList;
import java.util.concurrent.Exchanger;

public class Producer extends Thread
{
    private Exchanger<ArrayList<Integer>> exchanger;
    private ArrayList<Integer> buffer = new ArrayList<Integer>();

    public Producer( Exchanger<ArrayList<Integer>> exchanger ) {
        this.exchanger = exchanger;
    }

    @Override
    public void run() {

        while ( true ) {

            try {
                System.out.println( "Producer." );
                Thread.sleep( 1000 );
                this.FillBuffer();
                System.out.println( "Producer has produced and waiting: " + buffer );
                buffer = exchanger.exchange( buffer );
            }
            catch ( InterruptedException e ) {
                e.printStackTrace();
            }
        }
    }

    public void FillBuffer() {

        for ( int i = 0; i <= 3; i++ ) {
            buffer.add( i );
        }
    }
}
