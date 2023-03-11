/**
 * Created by justin on 2015-07-09.
 */

package Basic.Executor;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorCompletionService;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class Logic
{
    public static void TestExecutor() {

        {
            // Get an executor with three threads in its thread pool
            ExecutorService exec = Executors.newFixedThreadPool( 3 );

            // Completed task returns an object of the TaskResult class
            ExecutorCompletionService<Result> completionService = new ExecutorCompletionService<>( exec );

            for ( int i = 1; i <= 5; i++ ) {
                SleepingTask task = new SleepingTask( i, 3 );
                completionService.submit( task );
            }

            for ( int i = 1; i <= 5; i++ ) {
                try {
                    Future<Result> completedTask = completionService.take();
                    Result result = completedTask.get();
                    System.out.println( "Completed a task - " + result.ToString() );
                }
                catch ( ExecutionException e) {
                    System.out.println( e.getMessage() );
                    System.out.println( e.getCause().getMessage() );
                }
                catch( InterruptedException e ) {
                    e.printStackTrace();
                }
            }

            exec.shutdown();
        }

        /*{
            Callable<Object> badTask = () -> {
                throw new RuntimeException( "Throwing exception from task execution..." );
            };

            ExecutorService exec = Executors.newSingleThreadExecutor();
            Future submittedTask = exec.submit( badTask );

            try {
                Object result = submittedTask.get();
            }
            catch ( ExecutionException e) {
                System.out.println( e.getMessage() );
                System.out.println( e.getCause().getMessage() );
            }
            catch ( InterruptedException e ) {
                e.printStackTrace();
            }

            exec.shutdown();
        }*/

        /*{
            Runnable badTask = () -> {
                throw new RuntimeException( "Throwing exception from task execution...");
            };

            ExecutorService exec = Executors.newSingleThreadExecutor();
            exec.execute( badTask );
            exec.shutdown();
        }*/

        /*{
            // Get an executor with 3 threads
            ScheduledExecutorService sexec = Executors.newScheduledThreadPool( 3 );

            ScheduledTask task1 = new ScheduledTask( 1 );
            ScheduledTask task2 = new ScheduledTask( 2 );

            // Task #1 will run after 2 seconds
            sexec.schedule( task1, 2, TimeUnit.SECONDS );

            // Task #2 runs after 5 seconds delay and keep running every 10 seconds
            sexec.scheduleAtFixedRate( task2, 5, 10, TimeUnit.SECONDS );

            try {
                TimeUnit.SECONDS.sleep( 60 );
            }
            catch ( InterruptedException e ) {
                e.printStackTrace();
            }

            sexec.shutdown();
        }*/

        /*{
            // Get an executor with three threads in its thread pool
            ExecutorService exec = Executors.newFixedThreadPool( 3 ) ;

            CallableTask task = new CallableTask( 1 );

            // Submit the callable task to executor
            Future<Integer> submittedTask = exec.submit( task );

            try {
                Integer result = submittedTask.get();
                System.out.println( "Task's total sleep time: " + result + " seconds" );
            }
            catch ( InterruptedException e ) {
                e.printStackTrace();
            }
            catch ( ExecutionException e ) {
                e.printStackTrace();
            }

            exec.shutdown();
        }*/

        /*{
            final int THREAD_COUNT = 3;
            final int LOOP_COUNT = 3;
            final int TASK_COUNT = 5;

            // Get an executor with three threads in its thread pool
            ExecutorService exec = Executors.newFixedThreadPool( THREAD_COUNT );

            // Create five tasks and submit them to the executor
            for (int i = 1; i <= TASK_COUNT; i++) {

                RunnableTask task = new RunnableTask( i, LOOP_COUNT );
                exec.submit( task );
            }

            exec.shutdown();
        }*/
    }
}
