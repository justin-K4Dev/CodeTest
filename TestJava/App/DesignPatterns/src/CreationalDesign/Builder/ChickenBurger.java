package CreationalDesign.Builder;

/**
 * Created by justin on 2015-07-24.
 */

public class ChickenBurger extends Burger {

    @Override
    public float Price() {
        return 50.5f;
    }

    @Override
    public String Name() {
        return "Chicken Burger";
    }
}