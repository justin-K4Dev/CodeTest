package CreationalDesign.AbstractFactory;

/**
 * Created by justin on 2015-07-19.
 */

public class Circle implements Shape {

    @Override
    public void Draw() {
        System.out.println("Inside Circle::Draw() method.");
    }
}
