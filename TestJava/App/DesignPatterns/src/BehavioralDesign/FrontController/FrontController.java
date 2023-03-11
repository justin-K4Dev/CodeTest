package BehavioralDesign.FrontController;

/**
 * Created by justin on 2015-07-25.
 */

public class FrontController {

    private Dispatcher dispatcher;

    public FrontController(){
        dispatcher = new Dispatcher();
    }

    private boolean isAuthenticUser(){
        System.out.println("User is authenticated successfully.");
        return true;
    }

    private void trackRequest(String request){
        System.out.println("Page requested: " + request);
    }

    public void dispatchRequest(String request){
        //log each request
        trackRequest(request);

        //authenticate the user
        if(isAuthenticUser()){
            dispatcher.dispatch(request);
        }
    }
}