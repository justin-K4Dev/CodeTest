package CreationalDesign.AbstractFactory;

/**
 * Created by justin on 2015-07-19.
 */

public class Blue implements Color {

    @Override
    public void Fill() {
        System.out.println( "Inside Blue::Fill() method." );
    }
}
