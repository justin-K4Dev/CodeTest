/**
 * Created by justin on 2015-07-07.
 */

package Basic.Synchronizers.Semaphores;

import java.util.concurrent.Semaphore;

public class Restaurant
{
    private Semaphore tables;

    public Restaurant( int tablesCount ) {
        this.tables = new Semaphore( tablesCount );
    }

    public void GetTable(int customerID) {
        try {
            System.out.println( "Customer #" + customerID + " is trying to get a table." );
            tables.acquire();
            System.out.println( "Customer #" + customerID + " got a table." );
        }
        catch ( InterruptedException e ) {
            e.printStackTrace();
        }
    }

    public void ReturnTable( int customerID ) {
        System.out.println( "Customer #" + customerID + " returned a  table." );
        tables.release();
    }
}
