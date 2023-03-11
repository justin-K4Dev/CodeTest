package Interface;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Interface implementation

    Implementing an Interface

    An interface specifies a protocol that an object has to offer.

    A class may provide a partial implementation of the abstract methods of the interface,
    and in that case, the class must declare itself abstract.

    A class that implements an interface uses an "implements" clause to specify the name of the interface.

    An "implements" clause consists of the keyword implements, followed by a comma-separated list of interface types.

    A class can implement multiple interfaces.

    The general syntax for a class declaration that implements an interface looks as follows:

        <modifiers> class <class-Name> implements <comma-separated-list-of-interfaces>
        {
            // Class body  goes  here
        }

    Suppose there is a Circle class.

        public class Circle implements Shape
        {
           void draw() {
              System.out.println( "draw circle" );
           }
        }

    The class that implements an interface must override to implement all abstract methods declared in the interface.
    Otherwise, the class must be declared abstract.

    The default methods of an interface are also inherited by the implementing classes.
    The implanting classes may choose bu not required to override the default methods.
    The static methods in an interface are not inherited by the implementing classes.

    The following code defines two reference types, one is from class Circle the other is from interface type.

        Circle c = new Circle();
        Shape shape = new Circle();

    The variable c is of the Circle type. It is referring to the Circle object.

    The second assignment is also valid because the Circle class implements the Shape interface
    and every object of the Circle class is also of the Shape type.


    Implementing Interface Methods

    When a class fully implements an interface,
    it provides an implementation for all abstract methods of the implemented interfaces.

    A method declaration in an interface includes constraints for the methods.
    For example, the throws clause in the method declaration is a constraint for the method.

        import java.io.IOException;

        interface Shape
        {
            void draw( double amount ) throws IOException;
        }

        class Main implements Shape
        {
            @Override
            public void draw( double amount ) {
                // TODO Auto-generated method stub
            }
        }

    The code for Main is valid, even though it dropped the throws clause.
    Dropping constraints exceptions is allowed when a class overrides an interface method.

    If we use the Shape type, we have to handle the IOException.

        import java.io.IOException;

        interface Shape
        {
            void draw( double amount ) throws IOException;
        }

        class Main implements Shape
        {
            @Override
            public void draw( double amount ) {
                // TODO Auto-generated method stub
            }
            public void anotherMethod() {

                Shape s = new Main();
                try {
                    s.draw( 0 );
                }
                catch ( IOException e ) {
                    e.printStackTrace();
                }

                draw( 0 );
            }
        }


    Implementing Multiple Interfaces

    A class can implement multiple interfaces.
    All interfaces that a class implements are listed after the keyword implements in the class declaration.

    By implementing multiple interfaces,
    the class agrees to provide the implementation for all abstract methods in all interfaces.

        interface Adder
        {
            int add( int n1, int n2 );
        }

        interface Subtractor
        {
            int subtract( int n1, int n2 );
        }

        class Main implements Adder, Subtractor
        {
            public int add( int n1, int n2 ) {
                return n1 + n2;
            }

            public int subtract( int n1, int n2 ) {
                return n1 - n2;
            }
        }


    Partially Implementing an Interface

    A class does not have to provide implementations for all methods.
    If a class does not provide the full implementation of interfaces, it must be declared abstract.

        interface Calculator
        {
            int add( int n1, int n2 );
            int subtract( int n1, int n2 );
        }

        abstract class Main implements Calculator
        {
            public int add( int n1, int n2 ) {
                return n1 + n2;
            }
        }
 */

public class InterfaceImplementation {
}
