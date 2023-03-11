/**
 * Created by justin on 2015-06-29.
 */

package Example1;

public class Logic {

    public static void TestIOBuffer() {

        Buffer buffer = new Buffer();
        Producer p = new Producer( buffer );
        Consumer c = new Consumer( buffer );

        p.start();
        c.start();
    }
}
