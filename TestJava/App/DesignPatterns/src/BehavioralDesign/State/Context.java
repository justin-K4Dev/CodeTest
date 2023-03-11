package BehavioralDesign.State;

/**
 * Created by justin on 2015-07-25.
 */

public class Context {
    private State state;

    public Context(){
        state = null;
    }

    public void setState(State state){
        this.state = state;
    }

    public State getState(){
        return state;
    }
}