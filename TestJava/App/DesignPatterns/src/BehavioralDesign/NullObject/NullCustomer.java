package BehavioralDesign.NullObject;

/**
 * Created by justin on 2015-07-25.
 */

public class NullCustomer extends AbstractCustomer {

    @Override
    public String getName() {
        return "Not Available in Customer Database";
    }

    @Override
    public boolean isNil() {
        return true;
    }
}