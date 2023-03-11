package Basic.ExplicitLock;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Created by justin on 2015-06-11.
 */
public class ExplicitLock {

    private Lock lock = new ReentrantLock();

    public void UpdateState() {

        try {
            // Acquire the lock
            lock.lock();
        }
        finally {
            // Release the lock
            lock.unlock();
        }
    }

}
