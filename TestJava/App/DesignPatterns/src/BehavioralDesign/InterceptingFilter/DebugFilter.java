package BehavioralDesign.InterceptingFilter;

/**
 * Created by justin on 2015-07-25.
 */

public class DebugFilter implements Filter {
    public void execute(String request){
        System.out.println("request log: " + request);
    }
}