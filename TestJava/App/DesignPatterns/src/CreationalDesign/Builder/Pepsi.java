package CreationalDesign.Builder;

/**
 * Created by justin on 2015-07-24.
 */

public class Pepsi extends ColdDrink {

    @Override
    public float Price() {
        return 35.0f;
    }

    @Override
    public String Name() {
        return "Pepsi";
    }
}