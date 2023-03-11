package Inheritance;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Inheritance Hiding

    Method Hiding

    A class inherits all non-private static methods from its superclass.
    Redefining an inherited static method in a class is known as method hiding.

    The redefined static method in a subclass hides the static method of its superclass.
    Redefining a non-static method in a class is called method overriding.

    All rules about the redefined method (name, access level, return types, and exception)
    for method hiding are the same as for method overriding.

        class MySuper
        {
            public static void print() {
                System.out.println( "Inside MySuper.print()" );
            }
        }

        class MySubclass extends MySuper
        {
            public static void print() {
                System.out.println( "Inside MySubclass.print()" );
            }
        }

        public class Main
        {
            public static void main( String[] args ) {

                MySuper mhSuper = new MySubclass();
                MySubclass mhSub = new MySubclass();

                MySuper.print();
                MySubclass.print();

                ((MySuper) mhSub).print();

                mhSuper = mhSub;
                mhSuper.print();

                ((MySubclass) mhSuper).print();
            }
        }

    The code above generates the following result.
        Inside MySuper.print()
        Inside MySubclass.print()
        Inside MySuper.print()
        Inside MySuper.print()
        Inside MySubclass.print()


    Field Hiding

    A field declaration, static or non-static,
    in a class hides the inherited field with the same name in its superclass.

    The type of the field and its access level are not considered in the case of field hiding.
    Field hiding occurs solely based on the field name.

        class MySuper
        {
            protected int num = 100;
            protected String name = "Tom";
        }

        class MySub extends MySuper
        {
            public void print() {
                System.out.println( "num: " + num );
                System.out.println( "name: " + name );
            }
        }

        class MySub2 extends MySuper
        {
            // Hides num field in MySuper class
            private int num = 200;

            // Hides name field in MySuper class
            private String name = "Jack";

            public void print() {
                System.out.println( "num: " + num );
                System.out.println( "name: " + name );
            }
        }

        public class Main
        {
            public static void main( String[] args ) {

                MySub fhSub = new MySub();
                fhSub.print();
                MySub2 fhSub2 = new MySub2();
                fhSub2.print();
            }
        }

    The code above generates the following result.
        num: 100
        name: Tom
        num: 200
        name: Jack


    Example

    The following code shows how to Access Hidden Fields of Superclass Using the super Keyword

        class MySuper
        {
            protected int num = 100;
            protected String name = "Tom";
        }

        class MySub extends MySuper
        {
            // Hides the num field in MySuper class
            private int num = 200;

            // Hides the name field in MySuper class
            private String name = "Jack";

            public void print() {
                System.out.println( "num: " + num );
                System.out.println( "super.num: " + super.num );
                System.out.println( "name: " + name );
                System.out.println( "super.name: " + super.name );
            }
        }

        public class Main
        {
            public static void main( String[] args ) {
                MySub s = new MySub();
                s.print();
            }
        }

    The code above generates the following result.
        num: 200
        super.num: 100
        name: Jack
        super.name: Tom

    Field hiding occurs when a class declares a variable with the same name as an inherited variable from its superclass.
    Field hiding occurs only based on the name of the field.

    A class should use the keyword super to access the hidden fields of the superclass.
    The class can use the simple names to access the redefined fields in its body.
 */


public class InheritanceHiding {
}
