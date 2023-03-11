/**
 * Created by justin on 2015-06-12.
 */

package Example1;

public class Consumer extends Thread
{
    private Buffer buffer;

    public Consumer( Buffer buffer ) {
        this.buffer = buffer;
    }

    public void run() {
        int data;

        while( true ) {
            data = this.buffer.Consume();
        }
    }
}
