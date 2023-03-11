package CreationalDesign.AbstractFactory;

/**
 * Created by justin on 2015-07-19.
 */

/*
    Abstract Factory Pattern

    Abstract Factory patterns work around a super-factory which creates other factories.
    This factory is also called as factory of factories.

    This type of design pattern comes under creational pattern
    as this pattern provides one of the best ways to create an object.

    In Abstract Factory pattern an interface is responsible for creating a factory of related objects
    without explicitly specifying their classes.
    Each generated factory can give the objects as per the Factory pattern.

    Implementation

    We are going to create a Shape and Color interfaces and concrete classes implementing these interfaces.
    We create an abstract factory class AbstractFactory as next step.

    Factory classes ShapeFactory and ColorFactory are defined where each factory extends AbstractFactory.
    A factory creator/generator class FactoryProducer is created.

    AbstractFactoryPatternDemo, our demo class uses FactoryProducer to get a AbstractFactory object.
    It will pass information (CIRCLE / RECTANGLE / SQUARE for Shape) to AbstractFactory to get the type of object it needs.
    It also passes information (RED / GREEN / BLUE for Color) to AbstractFactory to get the type of object it needs.
 */

public class Logic {

    public static void Test() {

        //get shape factory
        AbstractFactory shapeFactory = FactoryProducer.GetFactory("SHAPE");

        //get an object of Shape Circle
        Shape shape1 = shapeFactory.GetShape("CIRCLE");

        //call draw method of Shape Circle
        shape1.Draw();

        //get an object of Shape Rectangle
        Shape shape2 = shapeFactory.GetShape("RECTANGLE");

        //call draw method of Shape Rectangle
        shape2.Draw();

        //get an object of Shape Square
        Shape shape3 = shapeFactory.GetShape("SQUARE");

        //call draw method of Shape Square
        shape3.Draw();

        //get color factory
        AbstractFactory colorFactory = FactoryProducer.GetFactory("COLOR");

        //get an object of Color Red
        Color color1 = colorFactory.GetColor("RED");

        //call fill method of Red
        color1.Fill();

        //get an object of Color Green
        Color color2 = colorFactory.GetColor("GREEN");

        //call fill method of Green
        color2.Fill();

        //get an object of Color Blue
        Color color3 = colorFactory.GetColor("BLUE");

        //call fill method of Color Blue
        color3.Fill();
    }
}
