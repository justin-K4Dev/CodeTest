package CreationalDesign.AbstractFactory;

/**
 * Created by justin on 2015-07-19.
 */
public class FactoryProducer {

    public static AbstractFactory GetFactory(String choice) {

        if( choice.equalsIgnoreCase( "Shape" ) ) {
            return new ShapeFactory();
        }
        else if( choice.equalsIgnoreCase( "Color" ) ) {
            return new ColorFactory();
        }

        return null;
    }
}
