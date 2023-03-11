package CreationalDesign.AbstractFactory;

/**
 * Created by justin on 2015-07-19.
 */

public class ColorFactory extends AbstractFactory {

    @Override
    public Shape GetShape(String shapeType){
        return null;
    }

    @Override
    Color GetColor(String color) {

        if(color == null){
            return null;
        }

        if(color.equalsIgnoreCase("RED")){
            return new Red();

        }else if(color.equalsIgnoreCase("GREEN")){
            return new Green();

        }else if(color.equalsIgnoreCase("BLUE")){
            return new Blue();
        }

        return null;
    }
}
