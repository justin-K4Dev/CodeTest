package BehavioralDesign.ServiceLocator;

/**
 * Created by justin on 2015-07-25.
 */

public class Service2 implements Service {
    public void execute(){
        System.out.println("Executing Service2");
    }

    @Override
    public String getName() {
        return "Service2";
    }
}