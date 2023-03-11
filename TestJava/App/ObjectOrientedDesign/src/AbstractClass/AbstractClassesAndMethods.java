package AbstractClass;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Abstract Classes and Methods

    Java can define a class whose objects cannot be created.
    Its purpose is just to represent an idea, which is common to objects of other classes.

    Such a class is called an abstract class.


    Syntax

    We need to use the abstract keyword in the class declaration to declare an abstract class.
    For example, the following code declares a Shape class abstract:

        public abstract class Shape
        {
        }

    The following code adds a draw() method to Shape class.

        public abstract class Shape
        {
            public Shape() {
            }
            public abstract void draw();
        }

    A abstract class does not necessarily mean that it has at least one abstract method.
    If a class has an abstract method either declared or inherited, it must be declared abstract.

    An abstract method is declared the same way as any other methods,
    except that its body is indicated by a semicolon.


    Example

    The following Shape class has both abstract and non-abstract methods.

        abstract class Shape
        {
            private String name;

            public Shape() {
                this.name = "Unknown  shape";
            }

            public Shape( String name ) {
                this.name = name;
            }

            public String getName() {
                return this.name;
            }

            public void setName(String name) {
                this.name = name;
            }

            // Abstract methods
            public abstract void draw();

            public abstract double getArea();

            public abstract double getPerimeter();
        }

    The following code shows how to create a Rectangle class, which inherits from the Shape class.

        class Rectangle extends Shape
        {
            private double width;
            private double height;

            public Rectangle( double width, double height ) {

                // Set the shape name as "Rectangle"
                super("Rectangle");
                this.width = width;
                this.height = height;
            }

            // Provide an implementation for inherited abstract draw() method
            public void draw() {
                System.out.println( "Drawing a rectangle..." );
            }

            // Provide an implementation for inherited abstract getArea() method
            public double getArea() {
                return width * height;
            }

            // Provide an implementation for inherited abstract getPerimeter() method
            public double getPerimeter() {
                return 2.0 * ( width + height );
            }
        }
 */


public class AbstractClassesAndMethods {
}
