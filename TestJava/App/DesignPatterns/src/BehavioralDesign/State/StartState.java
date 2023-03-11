package BehavioralDesign.State;

/**
 * Created by justin on 2015-07-25.
 */

public class StartState implements State {

    public void doAction(Context context) {
        System.out.println("Player is in start state");
        context.setState(this);
    }

    public String toString(){
        return "Start State";
    }
}