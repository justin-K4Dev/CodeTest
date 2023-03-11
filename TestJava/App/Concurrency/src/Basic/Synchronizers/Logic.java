/**
 * Created by justin on 2015-07-02.
 */

package Basic.Synchronizers;

import java.util.concurrent.Exchanger;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Phaser;
import java.util.concurrent.CyclicBarrier;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

import Basic.Synchronizers.Exchangers.*;
import Basic.Synchronizers.Latches.*;
import Basic.Synchronizers.Phasers.*;
import Basic.Synchronizers.Barriers.*;
import Basic.Synchronizers.Semaphores.*;

public class Logic
{
    public static void TestExchangers() {

        Exchanger<ArrayList<Integer>> exchanger = new Exchanger<>();

        Producer p = new Producer( exchanger );
        Consumer c = new Consumer( exchanger );

        p.start();
        c.start();

    }

    public static void TestLatches() {

        // Create a countdown latch with 2 as its counter
        CountDownLatch latch = new CountDownLatch(2);

        Manager m = new Manager(latch);
        m.start();

        for ( int i = 1; i <= 2; i++ ) {
            Helper h = new Helper( i, latch );
            h.start();
        }
    }

    public static void TestPharsers() {

        // Phaser Example 3
        {
            final int PHASE_COUNT = 2;

            Phaser phaser = new Phaser() {
                public boolean onAdvance( int phase, int parties ) {
                    System.out.println( "Phase:" + phase + ", Parties:" + parties + ", Arrived:" + this.getArrivedParties() );
                    boolean terminatePhaser = false;
                    if ( phase >= PHASE_COUNT - 1 || parties == 0 ) {
                        terminatePhaser = true;
                    }

                    return terminatePhaser;
                }
            };

            List<Integer> list = Collections.synchronizedList( new ArrayList<Integer>() );
            int ADDER_COUNT = 3;
            phaser.bulkRegister( ADDER_COUNT + 1 );
            for ( int i = 1; i <= ADDER_COUNT; i++ ) {
                String taskName = "Task #" + i;
                AdderTask w = new AdderTask( taskName, phaser, list );
                w.start();
            }

            while ( !phaser.isTerminated() ) {
                phaser.arriveAndAwaitAdvance();
            }

            int sum = 0;
            for ( Integer num : list ) {
                sum = sum + num;
            }
            System.out.println( "Sum = " + sum );
        }

        // Phaser Example 2
        {
            Phaser phaser = new Phaser() {
                protected boolean onAdvance( int phase, int parties ) {
                    System.out.println( "Inside onAdvance(): phase  = " + phase + ", Registered Parties = " + parties );
                    // Do not terminate the phaser by returning false
                    return false;
                }
            };

            // Register the self ( the "main" thread ) as a party
            phaser.register();
            System.out.println( "#1: isTerminated():" + phaser.isTerminated() );
            phaser.arriveAndDeregister();

            // Trigger another phase advance
            phaser.register();
            phaser.arriveAndDeregister();

            System.out.println( "#2: isTerminated():" + phaser.isTerminated() );
            phaser.forceTermination();
            System.out.println( "#3: isTerminated():" + phaser.isTerminated() );
        }

        // Phaser Example 1
        {
            Phaser phaser = new Phaser( 1 );

            for (int i = 1; i <= 3; i++) {
                phaser.register();

                String taskName = "Task #" + i;
                StartTask t = new StartTask( taskName, phaser );
                t.start();
            }
            phaser.arriveAndDeregister();
        }
    }

    public static void TestBarriers() {

        Runnable barrierAction = () -> System.out.println( "We are ready." );
        CyclicBarrier barrier = new CyclicBarrier( 3, barrierAction );

        for ( int i = 1; i <= 3; i++ ) {
            Worker t = new Worker( i, barrier );
            t.start();
        }
    }

    public static void TestSemaphores() {

        Restaurant restaurant = new Restaurant( 2 );
        for ( int i = 1; i <= 5; i++ ) {
            Guest g = new Guest( restaurant, i );
            g.start();
        }
    }
}
