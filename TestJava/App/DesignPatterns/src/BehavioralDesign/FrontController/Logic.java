package BehavioralDesign.FrontController;

/**
 * Created by justin on 2015-07-25.
 */

/*
    Front Controller Pattern

    The front controller design pattern is used to provide a centralized request handling mechanism
    so that all requests will be handled by a single handler.
    This handler can do the authentication/ authorization/ logging or tracking of request
    and then pass the requests to corresponding handlers.
    Following are the entities of this type of design pattern.

        Front Controller - Single handler for all kinds of requests coming to the application
                           (either web based/ desktop based).

        Dispatcher - Front Controller may use a dispatcher object which can dispatch the request to
                     corresponding specific handler.

        View - Views are the object for which the requests are made.

    Implementation

    We are going to create a FrontController and Dispatcher to act as Front Controller and Dispatcher correspondingly.
    HomeView and StudentView represent various views for which requests can come to front controller.

    FrontControllerPatternDemo, our demo class,
    will use FrontController to demonstrate Front Controller Design Pattern.
 */

public class Logic {

    public static void Test() {

        FrontController frontController = new FrontController();
        frontController.dispatchRequest("HOME");
        frontController.dispatchRequest("STUDENT");
    }
}
