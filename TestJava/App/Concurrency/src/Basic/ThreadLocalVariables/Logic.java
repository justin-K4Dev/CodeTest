/**
 * Created by justin on 2015-07-13.
 */

package Basic.ThreadLocalVariables;

public class Logic {

    public static void TestThreadLocalVariables() {

        new Thread( Logic::Run ).start();
        new Thread( Logic::Run ).start();
    }

    public static void Run() {

        int counter = 3;

        System.out.println( Thread.currentThread().getName() + " generated counter: " + counter );

        for (int i = 0; i < counter; i++) {
            CallTracker.Do();
        }
    }
}
