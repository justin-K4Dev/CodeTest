package BehavioralDesign.InterceptingFilter;

/**
 * Created by justin on 2015-07-25.
 */

public class Target {
    public void execute(String request){
        System.out.println("Executing request: " + request);
    }
}