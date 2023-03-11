package CreationalDesign.Factory;

/**
 * Created by justin on 2015-07-19.
 */

public class ShapeFactory {

    // use GetShape method to get object of type shape
    public Shape GetShape( String shapeType ) {
        if( shapeType == null ){
            return null;
        }

        if( shapeType.equalsIgnoreCase( "CIRCLE" ) ) {
            return new Circle();
        }
        else if( shapeType.equalsIgnoreCase( "RECTANGLE" ) ) {
            return new Rectangle();
        }
        else if( shapeType.equalsIgnoreCase( "SQUARE" ) ) {
            return new Square();
        }

        return null;
    }
}
