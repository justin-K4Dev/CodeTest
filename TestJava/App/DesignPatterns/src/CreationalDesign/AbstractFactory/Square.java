package CreationalDesign.AbstractFactory;

/**
 * Created by justin on 2015-07-19.
 */
public class Square implements Shape {

    @Override
    public void Draw() {
        System.out.println("Inside Square::Draw() method.");
    }
}