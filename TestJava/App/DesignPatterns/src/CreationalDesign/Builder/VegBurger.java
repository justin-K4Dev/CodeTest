package CreationalDesign.Builder;

/**
 * Created by justin on 2015-07-24.
 */

public class VegBurger extends Burger {

    @Override
    public float Price() {
        return 25.0f;
    }

    @Override
    public String Name() {
        return "Veg Burger";
    }
}
