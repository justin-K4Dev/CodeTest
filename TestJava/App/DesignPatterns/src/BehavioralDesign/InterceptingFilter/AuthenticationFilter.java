package BehavioralDesign.InterceptingFilter;

/**
 * Created by justin on 2015-07-25.
 */

public class AuthenticationFilter implements Filter {
    public void execute(String request){
        System.out.println("Authenticating request: " + request);
    }
}