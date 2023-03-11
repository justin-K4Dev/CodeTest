package Interface;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Interface Inheritance

    An interface can inherit from another interface. Unlike a class, an interface can inherit from multiple interfaces.

        interface Singer
        {
            void sing();
            void setRate( double rate );
            double getRate();
        }

        interface Writer
        {
            void write();
            void setRate( double rate );
            double getRate();
        }

        interface Player
        {
            void play();
            void setRate( double rate );
            default double getRate() {
                return 300.0;
            }
        }

    An interface uses the keyword extends to inherit from other interfaces.
    The keyword extends is followed by a comma-separated list of inherited interface names.

    The inherited interfaces are known as superinterfaces and the interface inheriting them is known as subinterface.

    An interface inherits the following members of its superinterfaces:

        * Abstract and default methods
        * Constant fields
        * Nested types

    An interface does not inherit static methods from its superinterfaces.

    An interface may override the inherited abstract and default methods that it inherits from its superinterfaces.

    If the super interface and child interface have the fields and nested types with the same names,
    the child interface wins.

        interface A
        {
            String s = "A";
        }

        interface B extends A
        {
            String s = "B";
        }

        public class Main
        {
            public static void main( String[] argv ) {
                System.out.println(B.s);
            }
        }

    The following code shows how to override the default method.

        interface A
        {
            default String getValue() {
                return "A";
            }
        }

        interface B extends A
        {
            default String getValue() {
                return "B";
            }
        }

        class MyClass implements B
        {
        }

        public class Main
        {
            public static void main( String[] argv ) {
                System.out.println( new MyClass().getValue() );
            }
        }

    The code above generates the following result.
        B


    Inheriting Conflicting Implementations

    Introduction of default methods made it possible for a class to inherit conflicting implementations
    from its superclass and superinterfaces.

    Java uses the three simple rules in order to resolve the conflict.

        1. superclass always wins
        2. most specific superinterface wins
        3. class must override the conflicting method


    instanceof Operator

    We can use the instanceof operator to evaluate if a reference type variable refers to an object of a specific class
    or its class implements a specific interface.

    The general syntax of the instanceof operator is

        referenceVariable instanceof ReferenceType

        interface A
        {
            default String getValue() {
                return "A";
            }
        }

        interface B
        {
            default String getValue() {
                return "B";
            }
        }

        class MyClass implements B, A
        {
            public String getValue(){
                return "B";
            }
        }

        public class Main
        {
            public static void main( String[] argv ) {

                MyClass myClass = new MyClass();

                System.out.println(myClass instanceof MyClass);
                System.out.println(myClass instanceof A);
                System.out.println(myClass instanceof B);
            }
        }

    The code above generates the following result.
        true
        true
        true

 */

public class InterfaceInheritance {
}
