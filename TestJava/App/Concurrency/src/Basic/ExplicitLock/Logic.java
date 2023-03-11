/**
 * Created by justin on 2015-07-02.
 */

package Basic.ExplicitLock;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Logic
{
    public int value;
    private ReentrantReadWriteLock rwLock = new ReentrantReadWriteLock();
    private Lock rLock = rwLock.readLock();
    private Lock wLock = rwLock.writeLock();

    public int GetValue() {

        rLock.lock();
        try {
            return this.value;
        }
        finally {
            rLock.unlock();
        }
    }

    public void SetValue( int value ) {

        wLock.lock();
        try {
            this.value = value;
        }
        finally {
            wLock.unlock();
        }
    }

    public static void TestExplicitLock() {

        Lock leftLock = new ReentrantLock();
        Lock rightLock = new ReentrantLock();

        Philosopher p = new Philosopher( leftLock, rightLock, "justin" );
        p.start();
    }
}
