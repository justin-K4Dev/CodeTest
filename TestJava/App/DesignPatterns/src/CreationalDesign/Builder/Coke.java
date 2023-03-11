package CreationalDesign.Builder;

/**
 * Created by justin on 2015-07-24.
 */

public class Coke extends ColdDrink {

    @Override
    public float Price() {
        return 30.0f;
    }

    @Override
    public String Name() {
        return "Coke";
    }
}