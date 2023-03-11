package CreationalDesign.AbstractFactory;

/**
 * Created by justin on 2015-07-19.
 */

public class Green implements Color {

    @Override
    public void Fill() {
        System.out.println( "Inside Green::Fill() method." );
    }
}
