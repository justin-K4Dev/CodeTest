/**
 * Created by justin on 2015-06-12.
 */

package Example1;

import java.util.Random;

public class Producer extends Thread
{
    private Buffer buffer;

    public Producer( Buffer buffer ) {
        this.buffer = buffer;
    }

    public void run() {
        Random rand = new Random();
        while ( true ) {
            int n = rand.nextInt();
            this.buffer.Produce( n );
        }
    }

}
