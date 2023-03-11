package CreationalDesign.Factory;

/**
 * Created by justin on 2015-07-19.
 */

/*
    Factory Pattern

    Factory pattern is one of most used design pattern in Java.

    This type of design pattern comes under creational pattern
    as this pattern provides one of the best ways to create an object.

    In Factory pattern, we create object without exposing the creation logic to the client
    and refer to newly created object using a common interface.

    Implementation

    We're going to create a Shape interface and concrete classes implementing the Shape interface.
    A factory class ShapeFactory is defined as a next step.

    FactoryPatternDemo, our demo class will use ShapeFactory to get a Shape object.
    It will pass information (CIRCLE / RECTANGLE / SQUARE) to ShapeFactory to get the type of object it needs.
 */

public class Logic {

    public static void Test() {

        ShapeFactory shapeFactory = new ShapeFactory();

        //get an object of Circle and call its Draw method.
        Shape shape1 = shapeFactory.GetShape("CIRCLE");

        //call draw method of Circle
        shape1.Draw();

        //get an object of Rectangle and call its Draw method.
        Shape shape2 = shapeFactory.GetShape("RECTANGLE");

        //call draw method of Rectangle
        shape2.Draw();

        //get an object of Square and call its Draw method.
        Shape shape3 = shapeFactory.GetShape("SQUARE");

        //call draw method of circle
        shape3.Draw();
    }
}
