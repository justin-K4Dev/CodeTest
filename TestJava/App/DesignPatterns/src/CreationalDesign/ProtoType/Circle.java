package CreationalDesign.ProtoType;

/**
 * Created by justin on 2015-07-24.
 */
public class Circle extends Shape {

    public Circle(){
        type = "Circle";
    }

    @Override
    public void Draw() {
        System.out.println( "Inside Circle::Draw() method." );
    }
}
