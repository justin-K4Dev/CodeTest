package CreationalDesign.AbstractFactory;

/**
 * Created by justin on 2015-07-19.
 */
public class ShapeFactory extends AbstractFactory {

    @Override
    public Shape GetShape(String shapeType) {

        if(shapeType == null){
            return null;
        }
        if(shapeType.equalsIgnoreCase("CIRCLE")){
            return new Circle();
        }
        else if(shapeType.equalsIgnoreCase("RECTANGLE")){
            return new Rectangle();
        }
        else if(shapeType.equalsIgnoreCase("SQUARE")){
            return new Square();
        }

        return null;
    }

    @Override
    Color GetColor(String color) {
        return null;
    }
}
