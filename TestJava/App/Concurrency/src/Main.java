/**
 * Created by justin on 2015-06-10.
 */


import Basic.Executor.*;
import Basic.Synchronizers.*;
import Basic.ExplicitLock.*;
import Basic.AtomicVariable.*;


public class Main {

    public static void main( String[] args ) {

        // ThreadLocal Variables Example
        {
            Basic.ThreadLocalVariables.Logic.TestThreadLocalVariables();
        }

        // ForkJoin Example
        {
            //Basic.ForkJoin.Logic.TestForkJoin();
        }

        // Executor Example
        {
            //Basic.Executor.Logic.TestExecutor();
        }

        // Synchronizers Exchangers Example
        {
            //Basic.Synchronizers.Logic.TestExchangers();
        }

        // Synchronizers Latches Example
        {
            //Basic.Synchronizers.Logic.TestLatches();
        }

        // Synchronizers Pharser Example
        {
            //Basic.Synchronizers.Logic.TestPharsers();
        }

        // Synchronizers Barriers Example
        {
            //Basic.Synchronizers.Logic.TestBarriers();
        }

        // Synchronizers Semaphores Example
        {
            //Basic.Synchronizers.Logic.TestSemaphores();
        }

        // Explicit Lock Example
        {
            //Basic.ExplicitLock.Logic.TestExplicitLock();
        }

        // Atomic variable Example
        {
            //Basic.AtomicVariable.Logic.TestAtomicVariable();
        }
    }
}
