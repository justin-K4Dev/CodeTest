/**
 * Created by justin on 2015-07-02.
 */

package Basic.AtomicVariable;


public class Logic {

    public static void TestAtomicVariable() {

        Worker t = new Worker();
        t.start();

        for( int i = 0; i < 10; i++ ) {

            try { Thread.sleep( 1000 ); }
            catch ( InterruptedException e ) { e.printStackTrace(); }
            long value = t.Decrement();
            System.out.println( "DecValue: " + value );
        }
    }
}
