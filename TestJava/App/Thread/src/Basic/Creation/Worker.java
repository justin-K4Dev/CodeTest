package Basic.Creation;

/**
 * Created by justin on 2015-06-29.
 */
public class Worker extends Thread
{
    @Override
    public void run() {
        System.out.println( "Hello Java Thread !!!" );
    }
}