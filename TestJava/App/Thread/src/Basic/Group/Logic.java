package Basic.Group;

/**
 * Created by justin on 2015-06-30.
 */
public class Logic
{
    public static void TestGroup() {

        {
            Thread t1 = Thread.currentThread();

            ThreadGroup tg1 = t1.getThreadGroup();

            System.out.println("Current thread's name: " + t1.getName());
            System.out.println("Current thread's group name: " + tg1.getName());

            Thread t2 = new Thread("My new thread");

            ThreadGroup tg2 = t2.getThreadGroup();
            System.out.println("New thread's name: " + t2.getName());
            System.out.println("New thread's group name: " + tg2.getName());
        }

        {
            ThreadGroup myGroup = new ThreadGroup( "My Thread Group" );
            Thread t = new Thread( myGroup, "myThreadName" );

            System.out.println( "New thread's name: " + t.getName() );
            System.out.println( "New thread's group name: " + myGroup.getName() );
        }
    }
}
