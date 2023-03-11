package Interface;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Interface as type

    An interface defines a new reference type.

    We can use an interface type to declare a variable, to declare a parameter type in a method,
    as a return type of a method, etc.

        interface Shape {
            void draw();
        }

        public class Main
        {
            // interface type as instance variable
            private Shape myShape;

            // interface type as parameter type for a constructor
            public Main( Shape s ) {
                this.myShape = s;
            }

            // interface type as return type of a method
            public Shape getShape() {
                return this.myShape;
            }

            // interface type as parameter type for a method
            public void setShape( Shape s ) {
                this.myShape = s;
            }

            public void letItSwim() {

                // interface type as a local variable
                Shape locaShape = null;

                locaShape = this.myShape;

                // interface variable can invoke methods
                // declared in the interface and the Object class
                locaShape.draw();
            }
        }


    Note

    A variable of an interface type refers to an object in memory whose class implements that interface.

    We can access any constant fields declared in an interface using a variable of the interface type
    or directly using the interface name.

    It is preferred to access the constants of an interface using the interface name.
    We can use a variable of an interface type to invoke any methods declared in the interface.

    A variable of an interface type can invoke any method of the java.lang.Object class.
    An instance or static variable of an interface type is initialized to null by default.
 */


public class InterfaceAsType {
}
