package InnerClass;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Static Inner Classes

    A static Member Class Is Not an Inner Class
    A member class defined within the body of another class may be declared static.


    Example

    The following code declares a top-level class A and a static member class B:

        class A
        {
            // Static member class
            public static class B
            {
                // Body for class B goes here
            }
        }


    Note

    A static member class is not an inner class. It is considered a top-level class.
    A static member class is also called a nested top-level class.

    An instance of class A and an instance of class B can exist independently because both are top-level classes.
    A static member class can be declared public, protected, package-level,
    or private to restrict its accessibility outside its enclosing class.

    There are two advantages of using a static member class:

        * A static member class can access the static members of its enclosing class
          including the private static members.

        * A package acts like a container for top-level classes by providing a namespace.
          Top-level classes having static member classes provide an additional layer of namespaces.

        * A static member class is the direct member of its enclosing top-level class, not a member of the package.

    An object of a static member class is created the same way
    as you create an object of a top-level class using the new operator.
    To create an object of class B, you write

        A.B bReference = new A.B();

    Since the simple name of class B is in the scope inside class A,
    we can use its simple name to create its object inside class A as

        B  bReference2 = new B(); // This  statement appears inside class  A  code

    We can also use the simple name B outside class A by importing the com.java2s.innerclasses.A.B class.


    Example 2

    The following code shows how to use static inner class.

        public class Main
        {
            public static void main( String[] args ) {

                Car.Tire m = new Car.Tire( 17 );
                Car.Tire m2 = new Car.Tire( 19 );

                Car.Keyboard k = new Car.Keyboard( 122 );
                Car.Keyboard k1 = new Car.Keyboard( 142 );

                System.out.println( m );
                System.out.println( m2 );
                System.out.println( k );
                System.out.println( k1 );
            }
        }

        class Car
        {
            // Static member class - Monitor
            public static class Tire
            {
                private int size;

                public Tire(int size) {
                    this.size = size;
                }

                public String toString() {
                    return "Monitor - Size:" + this.size + "  inch";
                }
            }

            // Static member class - Keyboard
            public static class Keyboard
            {
                private int keys;

                public Keyboard(int keys) {
                    this.keys = keys;
                }

                public String toString() {
                    return "Keyboard - Keys:" + this.keys;
                }
            }
        }
 */


public class StaticInnerClasses {
}
