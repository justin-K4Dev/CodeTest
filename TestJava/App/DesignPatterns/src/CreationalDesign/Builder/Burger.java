package CreationalDesign.Builder;

/**
 * Created by justin on 2015-07-24.
 */

public abstract class Burger implements Item {

    @Override
    public Packing Packing() {
        return new Wrapper();
    }

    @Override
    public abstract float Price();
}
