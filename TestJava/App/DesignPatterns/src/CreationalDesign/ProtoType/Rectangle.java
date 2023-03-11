package CreationalDesign.ProtoType;

/**
 * Created by justin on 2015-07-24.
 */
public class Rectangle extends Shape {

    public Rectangle(){
        type = "Rectangle";
    }

    @Override
    public void Draw() {
        System.out.println( "Inside Rectangle::Draw() method." );
    }
}
