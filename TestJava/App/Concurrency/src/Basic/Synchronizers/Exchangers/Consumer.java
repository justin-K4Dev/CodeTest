/**
 * Created by justin on 2015-07-08.
 */

package Basic.Synchronizers.Exchangers;

import java.util.ArrayList;
import java.util.concurrent.Exchanger;

public class Consumer extends Thread
{
    private Exchanger<ArrayList<Integer>> exchanger;
    private ArrayList<Integer> buffer = new ArrayList<Integer>();

    public Consumer( Exchanger<ArrayList<Integer>> exchanger ) {
        this.exchanger = exchanger;
    }

    @Override
    public void run() {

        while ( true ) {
            try {
                System.out.println( "Consumer." );
                buffer = exchanger.exchange( buffer );
                System.out.println( "Consumer  has received:" + buffer );
                Thread.sleep( 1000 );
                System.out.println( "eating:" + buffer );
                buffer.clear();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
