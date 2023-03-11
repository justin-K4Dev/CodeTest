package BehavioralDesign.Observer;

/**
 * Created by justin on 2015-07-24.
 */

public abstract class Observer {
    protected Subject subject;
    public abstract void update();
}