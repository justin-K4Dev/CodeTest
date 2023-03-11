package CreationalDesign.ProtoType;

/**
 * Created by justin on 2015-07-24.
 */

import java.util.Hashtable;


public class ShapeProtoType {

    private static Hashtable<String, Shape> shapeMap = new Hashtable<String, Shape>();

    public static Shape GetShape( String shapeId ) {

        Shape cachedShape = shapeMap.get( shapeId );
        return (Shape) cachedShape.clone();
    }

    public static void LoadCache() {

        Circle circle = new Circle();
        circle.SetID( "1" );
        shapeMap.put( circle.GetID(), circle );

        Square square = new Square();
        square.SetID( "2" );
        shapeMap.put( square.GetID(), square );

        Rectangle rectangle = new Rectangle();
        rectangle.SetID( "3" );
        shapeMap.put( rectangle.GetID(), rectangle );
    }
}
