package BehavioralDesign.BusinessDelegate;

/**
 * Created by justin on 2015-07-25.
 */

public class EJBService implements BusinessService {

    @Override
    public void doProcessing() {
        System.out.println("Processing task by invoking EJB Service");
    }
}