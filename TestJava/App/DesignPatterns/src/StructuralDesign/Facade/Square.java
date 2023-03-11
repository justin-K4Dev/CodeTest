package StructuralDesign.Facade;

/**
 * Created by justin on 2015-07-24.
 */

public class Square implements Shape {

    @Override
    public void draw() {
        System.out.println("Square::draw()");
    }
}