package CreationalDesign.ProtoType;

/**
 * Created by justin on 2015-07-24.
 */
public class Square extends Shape {

    public Square(){
        type = "Square";
    }

    @Override
    public void Draw() {
        System.out.println( "Inside Square::Draw() method." );
    }
}