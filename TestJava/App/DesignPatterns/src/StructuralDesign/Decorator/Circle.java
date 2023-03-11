package StructuralDesign.Decorator;

/**
 * Created by justin on 2015-07-24.
 */

public class Circle implements Shape {

    @Override
    public void draw() {
        System.out.println("Shape: Circle");
    }
}