package InnerClass;

/**
 * Created by justin on 2015-08-10.
 */


/*
    Data Type

    What Is an Inner Class?

    A class which is a member of a package is known as a top-level class.
    A class can be declared within another class. This type of class is called an inner class.

    If the class declared within another class is explicitly or implicitly declared static,
    it is called a nested class, not an inner class.

    The class that contains the inner class is called an enclosing class or an outer class.


    Example

    The following code declares an inner class.

        class Outer
        {
            public class Inner
            {
                // Members of the Inner class go here
            }
            // Other members of the Outer class go here
        }

    The Outer class is a top-level class.

    The Inner class is an inner class. It is a member of the Outer class.

    The Outer class is the enclosing (outer) class for the Inner class.

    An inner class can be the enclosing class for another inner class.
    There are no limits on the levels of nesting of inner classes.

    An instance of an inner class can only exist within an instance of its enclosing class.


    Advantages of Using Inner Classes
    The following are some of the advantages of inner classes.

        * define classes near other classes that will use them.

        * provide an additional namespace to manage class structures.

        * Some design patterns are easier to implement using inner classes.

        * Implementing a callback mechanism is elegant and convenient using inner classes.
          It helps implement closures in Java.


    Restrictions on Accessing Local Variables

    The following code demonstrates the rules for accessing local variables inside a local inner class.

    The main() method declares two local variables called x and y. Both variables are effectively final.

    The variable x is never changed after it is initialized and the variable y cannot be changed
    because it is declared as final.

        public class Main
        {
            public static void main( String... args ) {

                int x = 1;
                final int y = 2;

                class LocalInner
                {
                    void print() {
                        System.out.println( "x = " + x );
                        System.out.println( "y = " + y );
                    }
                }

                // Uncomment the following statement will make the variable x no longer
                // an effectively final variable and the LocalIneer class will not compile.
                // x = 100;

                LocalInner li = new LocalInner();
                li.print();
            }
        }

    The code above generates the following result.
        x = 1
        y = 2


    Inner Class and Inheritance

    An inner class can inherit from another inner class, a top-level class, or its enclosing class.

        class A
        {
            public class B
            {
            }

            public class C extends B
            {
            }

            public class D extends A
            {
            }
        }

        class E extends A
        {
            public class F extends B
            {
            }
        }


    No static Members in an Inner Class

    The keyword static in Java makes a construct a top-level construct.
    Therefore, we cannot declare any static members ( fields, methods, or initializers ) for an inner class.

    It is allowed to have static fields in an inner class that are compile-time constants.

        class A {
            public class B {

                public final static int DAYS_IN_A_WEEK = 7; // OK
                public final String str = new String( "Hello" );
            }
        }


    Generated Class Files for Inner Classes

    Each inner class is compiled into a separate class file.
    The class file name format for a member inner class and a static inner class is as follows:

        <outer-class-name>$<member-or-static-inner-class-name>

    The format for the class file name for a local inner class is as follows:

        <outer-class-name>$<a-number><local-inner-class-name>

    The format for the class file name for an anonymous class is as follows:

        <outer-class-name>$<a-number>

    <a-number> in a class file name is a number that is generated sequentially
    starting from 1 to avoid any name conflicts.


    Inner Classes in Static Contexts

    We can define an inner class in a static context such as inside a static method or a static initializer.
    All static field members are accessible to such an inner class.

        class Outer
        {
            static int k = 1;
            int m = 2;

            public static void staticMethod() {

                // Class Inner is defined in a static context
                class Inner
                {
                    int j = k; // OK. Referencing static field k
                    // int n = m; // An error. Referencing non-static field m
                }
            }
        }

 */

public class DataType {
}
