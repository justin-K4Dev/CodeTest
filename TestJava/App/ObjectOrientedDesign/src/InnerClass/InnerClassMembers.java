package InnerClass;

/**
 * Created by justin on 2015-08-11.
 */


/*
    Inner Class Members

    An inner class has access to all instance members, instance fields, and instance methods of its enclosing class.

        class Outer
        {
            private int value = 2014;

            public class Inner
            {
                public void printValue() {
                    System.out.println( "Inner: Value = " + value );
                }
            } // Inner class ends here

            public void printValue() {
                System.out.println( "Outer: Value = " + value );
            }

            public void setValue( int newValue ) {
                this.value = newValue;
            }
        }

        public class Main
        {
            public static void main( String[] args ) {

                Outer out = new Outer();
                Outer.Inner in = out.new Inner();

                out.printValue();
                in.printValue();

                out.setValue( 2015 );

                out.printValue();
                in.printValue(); // print "2015"
            }
        }

    The code above generates the following result.
        Outer: Value = 2014
        Inner: Value = 2014
        Outer: Value = 2015
        Inner: Value = 2015


    Example

    The following code shows how to access inner variable for inner class.

        public class Main
        {
            public static void main( String[] args ) {

                Outer out = new Outer();
                Outer.Inner in = out.new Inner();

                out.printValue();
                in.printValue();

                out.setValue( 3 );

                out.printValue();
                in.printValue();
            }
        }

        class Outer
        {
            private int value = 1;
            public class Inner
            {
                private int value = 2;
                public void printValue() {
                    System.out.println( "Inner: Value = " + value );
                }
            } // Inner class ends here

            public void printValue() {
                System.out.println( "Outer: Value = " + value );
            }

            public void setValue( int newValue ) {
                this.value = newValue;
            }
        }


    this keyword for Inner class

    The following code shows how to use the keyword this in the inner class.

        class Outer
        {
            private int value = 1;

            class QualifiedThis
            {
                private int value = 2;

                public void printValue() {
                    System.out.println( "value=" + value );
                    System.out.println( "this.value=" + this.value );
                    System.out.println( "QualifiedThis.this.value=" + QualifiedThis.this.value );
                }

                public void printHiddenValue() {
                    int value = 2;
                    System.out.println( "value=" + value );
                    System.out.println( "this.value=" + this.value );

                    System.out.println( "QualifiedThis.this.value=" + QualifiedThis.this.value );
                }
            }

            public void printValue() {
                System.out.println( "value=" + value );
                System.out.println( "this.value=" + this.value );
            }
        }

        public class Main
        {
            public static void main( String[] args ) {

                Outer outer = new Outer();
                Outer.QualifiedThis qt = outer.new QualifiedThis();
                System.out.println( "printValue():" );
                qt.printValue();

                System.out.println( "printHiddenValue():" );
                qt.printHiddenValue();
                outer.printValue();
            }
        }

    The code above generates the following result.
        printValue():
        value=2
        this.value=2
        QualifiedThis.this.value=2
        printHiddenValue():
        value=2
        this.value=2
        QualifiedThis.this.value=2
        value=1
        this.value=1


    Hidden variable

    If the instance variable name is hidden,
    you must qualify its name with the keyword this or the class name as well as the keyword this.

        class TopLevelOuter
        {
            private int v1 = 100;

            // Here, only v1 is in scope
            public class InnerLevelOne
            {
                private int v2 = 200;

                // Here, only v1 and v2 are in scope
                public class InnerLevelTwo
                {
                    private int v3 = 300;

                    // Here, only v1, v2, and v3 are in scope
                    public class InnerLevelThree
                    {
                        private int v4 = 400;

                        // Here, all v1, v2, v3, and v4 are in scope
                    }
                }
            }
        }


    From outer class

    The following code shows how to reference the variable from the outer class.

        public class Test
        {
            private int value = 1;

            public class Inner
            {
                private int value = 2;

                public void printValue() {
                    System.out.println( "Inner: Value = " + value );
                    System.out.println( "Outer: Value = " + Test.this.value );
                }
            } // Inner class ends here

            public void printValue() {
                System.out.println( "\nOuter - printValue()..." );
                System.out.println( "Outer: Value = " + value );
            }

            public void setValue(int newValue) {
                System.out.println( "\nSetting Outer's value to " + newValue );
                this.value = newValue;
            }
        }
*/

public class InnerClassMembers {
}
