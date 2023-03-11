package Interface;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Interface Methods

    Methods Declarations
    You can declare three types of methods in an interface:

        * Abstract methods
        * Static methods
        * Default methods

    Prior to Java 8, you could declare only abstract methods in interfaces.
    The modifiers static and default are used to declare static and default methods, respectively.

    The lack of static and default modifiers makes a method abstract.

    The following is an example of an interface with all three types of methods:

        interface AnInterface
        {
            // An abstract method
            int m1();

            // A static method
            static int m2()  {
                // The method  implementation goes  here
            }

            // A default method
            default int m3() {
                // The method implementation goes here
            }
        }


    Abstract Methods Declarations

    All method declarations in an interface are implicitly abstract
    and public unless they are declared static or default.

    An abstract method in an interface does not have an implementation.

    The body of the abstract method is always represented by a semicolon, not by a pair of braces.

    The following code declares an interface named Player:

        public interface Player
        {
            public abstract void play();

            public abstract void stop();

            public abstract void forward();

            public abstract void rewind();
        }

    The Player interface is a specification for an audio/video player.

    A real player, for example, a DVD player, will provide the concrete implementation of the specification
    by implementing all four methods of the Player interface.

    Use of the abstract and public keywords in a method declaration in an interface is redundant.

    The above declaration of the Player interface can be rewritten as follows without changing its meaning:

        public interface Player
        {
            void  play();
            void  stop();
            void  forward();
            void  rewind();
        }

    Abstract method declarations in an interface may include parameters, a return type, and a throws clause.

        public interface NewPlayer
        {
            boolean play(int account) throws AccountNotFoundException;

            boolean stop(double amount);

            boolean forward(double amount) throws InsufficientBalanceException;

            double rewind();
        }

    Abstract methods from an interface are implemented by classes that implement the interface,
    and classes override them to provide an implementation.

    An abstract method in an interface cannot be declared final.

    A class may declare the overridden method of an interface final indicating
    that the subclasses cannot override the method.


    Static Methods Declarations

    From Java 8, we can have static methods in interfaces.
    A static method contains the static modifier and are implicitly public.

    We can redefine the Walkable interface to include the letThemWalk() method.

        interface Walkable
        {
            // An abstract method
            void walk();

            // A static convenience method
            public static void letThemWalk( Walkable[] list ) {
                for ( int i = 0; i < list.length; i++ ) {
                  list[i].walk();
                }
            }
        }

    You can use the static methods of an interface using the dot notation.

        <interface-name>.<static-method>

    Unlike static methods in a class, static methods in an interface are not inherited by implementing classes
    or subinterfaces.

    An interface that inherits from another interface is called a subinterface.
    There is only one way to call the static methods of an interface:
        by using the interface name.

    A static method myStaticMethod() of an interface MyInterface must be called using MyInterface.myStaticMethod().

    We can use the unqualified name myStaticMethod() of the method to call it only within the body of the interface
    or when we import the method using a static import statement.


    Default Methods Declarations

    A default method in an interface is declared with the modifier default.
    The default method is added new feature in Java 8.

    A default method provides a default implementation for the classes that implements the interface,
    but does not override the default method.

    Suppose, we have the following interface.

        interface Shape
        {
            void setX(double x);
            void setY(double y);
            double getX();
            double getY();
        }

    The following code shows a Circle which implement the Shape interface.

        class Circle implements Movable
        {
            private double x;
            private double y;

            public Circle() {
            }

            public Circle(double x, double y) {
                this.x = x;
                this.y = y;
            }

            public void setX(double x) {
                this.x = x;
            }

            public void setY(double y) {
                this.y = y;
            }

            public double getX() {
                return x;
            }

            public double getY() {
                return y;
            }

            public String toString() {
                return "Circle( " + x + ", " + y + " )";
            }
        }

    If we add a new method to Shape as follows.

        interface Shape
        {
            void setX(double x);

            void setY(double y);

            double getX();

            double getY();

            void move(double deltaX, double deltaY);
        }

    Prior to Java 8, the new method move() is an abstract method.
    All classes that are implementing the Shape interface must provide the implementation for the new method.

    Pen class which implements the Shape interface will not compile anymore unless the new method is added to those classes.

    Prior to Java 8, it was not possible to add methods to an interface after it has been distributed to the public,
    without breaking the existing code.

    Java interface default methods is the accepted solution to evolve interfaces.
    A default method can be added to an existing interface and provides a default implementation for the method.

    All classes implementing the interface will inherit the default implementation,
    thus not breaking them. Classes may choose to override the default implementation.

    A default method is declared using the keyword default.
    A default method cannot be declared abstract or static. It must provide an implementation.
    Otherwise, a compile-time error occurs.

    The following code changes the Shape interface with a default method.

        interface Movable
        {
            void setX(double x);
            void setY(double y);

            double getX();
            double getY();

            // A default method
            default void move( double deltaX, double deltaY ) {

                double newX = getX() + deltaX;
                double newY = getY() + deltaY;
                setX(newX);
                setY(newY);
            }
        }

    The follow items list the similarities and differences between a concrete method in a class
    and a default method in an interface.

    Both have access to the keyword this in the same way.
    The keyword this is the reference of the object on which the method is called.

    A concrete method in a class can access the instance variables of the class.
    A default method does not have access to the instance of variables of the class implementing the interface.

    The default method has access to the other members of the interface.

    Both types of methods can use their parameters.
    Both methods can have a throws clause.

    A nested type declaration in an interface defines a new reference type.
    We can declare a class, interface, enum, and annotation as nested types.

    An interface/class declared inside an interface is called a nested interface/class.
    An interface and a class define new reference types, so do a nested interface and a nested class.

    A nested interface is always accessed through its enclosing interface.
    We can also declare a nested class inside an interface.

    The Job Interface with a Nested Class and a Constant Field.

        interface Task
        {
            class EmptyTask implements Task
            {
                private EmptyTask() {
                }

                public void runJob() {
                    System.out.println( "Empty..." );
                }
            }

            // A constant field
            Task EMPTY_JOB = new EmptyTask();

            void runJob();
        }

        public class Main
        {
            public static void main(String[] args) {

                submitJob( Task.EMPTY_JOB );
            }

            public static void submitJob( Task job ) {

                job.runJob();
            }
        }
 */


public class InterfaceMethods {
}
