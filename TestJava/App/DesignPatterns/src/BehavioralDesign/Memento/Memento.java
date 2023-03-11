package BehavioralDesign.Memento;

/**
 * Created by justin on 2015-07-24.
 */

public class Memento {
    private String state;

    public Memento(String state){
        this.state = state;
    }

    public String getState(){
        return state;
    }
}