/**
 * Created by justin on 2015-06-11.
 */


public class Main {

    public static void main( String[] args ) {

        // Thread State Example
        {
            Basic.ThreadState.Logic.TestThreadState();
        }

        // Volatile Variables Example
        {
            Basic.VolatileVariables.Logic.TestVolatileVariables();
        }

        // Thread Group Example
        {
            Basic.Group.Logic.TestGroup();
        }

        // Thread Interrupt Example
        {
            Basic.Interrupt.Logic.TestInterrupt();
        }

        // Thread Daemon Example
        {
            Basic.Daemon.Logic.TestDaemon();
        }

        // Thread LeftCycle Example
        {
            Basic.Priority.Logic.TestPriority();
        }

        // Thread LeftCycle Example
        {
            Basic.Priority.Logic.TestPriority();
        }

        // Thread LeftCycle Example
        {
            Basic.LeftCycle.Logic.TestLeftCycle();
        }

        // Thread Join Example
        {
            Basic.Join.Logic.TestJoin();
        }

        // Thread Sleep Example
        {
            Basic.Sleep.Logic.TestSleep();
        }

        // Thread Producer / Consumer Example
        {
            Example1.Logic.TestIOBuffer();
        }

        // Current Thread Example
        {
            Basic.CurrentThread.Logic.TestException();
            Basic.CurrentThread.Logic.TestCurrentThread();
        }

        // Multiple-Thread Example
        {
            Basic.MultipleThreads.Logic.TestNotify();
            Basic.MultipleThreads.Logic.TestMultipleThread();
        }

        // Thread Creation Example
        {
            Basic.Creation.Logic.TestMethod();
            Basic.Creation.Logic.TestRunnable();
            Basic.Creation.Logic.TestWorkerThread();
            Basic.Creation.Logic.TestThread();
        }
    }
}
