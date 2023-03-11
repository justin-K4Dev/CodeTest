package StructuralDesign.Facade;

/**
 * Created by justin on 2015-07-24.
 */

public class Rectangle implements Shape {

    @Override
    public void draw() {
        System.out.println("Rectangle::draw()");
    }
}