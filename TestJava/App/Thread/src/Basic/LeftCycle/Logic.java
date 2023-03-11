/**
 * Created by justin on 2015-06-30.
 */

package Basic.LeftCycle;

public class Logic {

    public static void TestLeftCycle() {

        Object syncObject = new Object();
        Worker ts = new Worker( syncObject );
        System.out.println( "Before start() - ts.isAlive(): " + ts.isAlive() );
        System.out.println( "#1: " + ts.getState() );

        ts.start();
        System.out.println( "After start() - ts.isAlive(): " + ts.isAlive() );
        System.out.println( "#2: " + ts.getState() );
        ts.SetWait( true );

        try {
            Thread.currentThread().sleep( 100 );
        }
        catch ( InterruptedException e ) {
            e.printStackTrace();
        }

        synchronized ( syncObject ) {
            System.out.println( "#3: " + ts.getState() );
            ts.SetWait( false );
            syncObject.notifyAll();
        }

        try {
            Thread.currentThread().sleep( 2000 );
        }
        catch ( InterruptedException e ) {
            e.printStackTrace();
        }

        System.out.println( "#4: " + ts.getState() );
        ts.SetKeepRunning( false );

        try {
            Thread.currentThread().sleep( 2000 );
        }
        catch ( InterruptedException e ) {
            e.printStackTrace();
        }

        System.out.println( "#5: " + ts.getState() );
        System.out.println( "At the end - ts.isAlive(): " + ts.isAlive() );
    }
}
