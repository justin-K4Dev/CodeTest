/**
 * Created by justin on 2015-07-02.
 */

package Basic.ExplicitLock;

import java.util.concurrent.locks.Lock;

public class Philosopher extends Thread
{
    private Lock leftFork;
    private Lock rightFork;
    private String name;

    public Philosopher( Lock leftFork, Lock rightFork, String name ) {
        this.leftFork = leftFork;
        this.rightFork = rightFork;
        this.name = name;
    }

    public void Think() {
        System.out.println( name + " is thinking..." );
    }

    public boolean Eat() {

        boolean result = false;

        if ( leftFork.tryLock() ) {
            try {
                if ( rightFork.tryLock() ) {
                    try {
                        System.out.println( name + " is eating..." );
                        result = true;
                    }
                    finally {
                        rightFork.unlock();
                    }
                }
            }
            finally {
                leftFork.unlock();
            }
        }

        return result;
    }

    @Override
    public void run() {

        while( true ) {

            this.Think();
            if( true == this.Eat() ) {
                return;
            }
        }
    }
}
