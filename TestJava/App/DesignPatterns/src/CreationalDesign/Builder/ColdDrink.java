package CreationalDesign.Builder;

/**
 * Created by justin on 2015-07-24.
 */

public abstract class ColdDrink implements Item {

    @Override
    public Packing Packing() {
        return new Bottle();
    }

    @Override
    public abstract float Price();
}