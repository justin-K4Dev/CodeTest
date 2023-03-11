package InnerClass;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Inner Class Objects

    Objects of a local inner class are created using the new operator inside the block, which declares the class.
    An object of an anonymous class is created at the same time the class is declared.

    A static member class is another type of top-level class.
    You create objects of a static member class the same way you create objects of a top-level class.
    An instance of a member inner class always exists within an instance of its enclosing class.


    Syntax

    The general syntax to create an instance of a member inner class is as follows:

        OuterClassReference.new MemberInnerClassConstructor()

    OuterClassReference is the reference of the enclosing class followed by a dot that is followed by the new operator.


    Example

    The member inner class's constructor call follows the new operator.

        class Outer
        {
            public class Inner
            {
            }
        }

    To create an instance of the Inner member inner class,
    you must first create an instance of its enclosing class Outer.

        Outer out = new Outer();

    Now, you need to use the new operator on the out reference variable to create an object of the Inner class.

        out.new Inner();

    To store the reference of the instance of the Inner member inner class in a reference variable,
    we can write the following statement:

        Outer.Inner in = out.new Inner();

    The following code shows how to create Objects of a Member Inner Class

        public class Main
        {
            public static void main( String[] args ) {

                Car c = new Car();
                Car.Tire t = c.new Tire( 9 );
            }
        }

        class Car
        {
            public class Tire
            {
                private int size;

                public Tire( int size ) {
                    this.size = size;
                }

                public String toString() {
                    return "Monitor - Size:" + this.size + " inch";
                }
            }
        }
 */

public class InnerClassObjects {
}
