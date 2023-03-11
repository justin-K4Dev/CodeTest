package InnerClass;

/**
 * Created by justin on 2015-08-11.
 */


/*
    Inner Classes Types

    You can define an inner class anywhere inside a class where you can write a Java statement.

    There are three types of inner classes.
    The type of inner class depends on the location and the way it is declared.

        * Member inner class
        * Local inner class
        * Anonymous inner class


    Member Inner Class

    A member inner class is declared inside a class the same way a member field or a member method is declared.
    It can be declared as public, private, protected, or package-level.

    The instance of a member inner class may exist only within the instance of its enclosing class.
    The following code creates a member inner class.

        class Car
        {
            private int year;

            // A member inner class named Tire public
            class Tire
            {
                private double radius;

                public Tire( double radius ) {
                    this.radius = radius;
                }

                public double getRadius() {
                    return radius;
                }
            } // Member inner class declaration ends here

            // A constructor for the Car class
            public Car( int year ) {
                this.year = year;
            }

            public int getYear() {
                return year;
            }
        }


    Local Inner Class

    A local inner class is declared inside a block.
    Its scope is limited to the block in which it is declared.

    Since its scope is limited to its enclosing block,
    its declaration cannot use any access modifiers such as public, private, or protected.

    Typically, a local inner class is defined inside a method.
    However, it can also be defined inside static initializers, non-static initializers, and constructors.

    The following code shows an example of a local inner class.

        import java.util.ArrayList;
        import java.util.Iterator;

        public class Main
        {
            public static void main( String[] args ) {

                StringList tl = new StringList();
                tl.addTitle( "A" );
                tl.addTitle( "B" );

                Iterator iterator = tl.titleIterator();
                while ( iterator.hasNext() ) {
                    System.out.println(iterator.next());
                }
            }
        }

        class StringList
        {
            private ArrayList<String> titleList = new ArrayList<>();

            public void addTitle( String title ) {
                titleList.add( title );
            }

            public void removeTitle( String title ) {
                titleList.remove( title );
            }

            public Iterator<String> titleIterator() {

                // A local inner class - TitleIterator
                class TitleIterator implements Iterator<String>
                {
                    int count = 0;

                    @Override
                    public boolean hasNext() {
                        return (count < titleList.size());
                    }

                    @Override
                    public String next() {
                        return titleList.get( count++ );
                    }
                }

                TitleIterator titleIterator = new TitleIterator();
                return titleIterator;
            }
        }

    The code above generates the following result.
        A
        B


    Example

    The following code has a local inner class which inherits from another public class.

        import java.util.Random;

        abstract class IntGenerator
        {
            public abstract int getValue();
        }

        class LocalGen
        {
            public IntGenerator getRandomInteger() {

                class RandomIntegerLocal extends IntGenerator
                {
                    @Override
                    public int getValue() {
                        Random rand = new Random();
                        long n1 = rand.nextInt();
                        long n2 = rand.nextInt();
                        int value = (int) ( (n1 + n2) / 2 );
                        return value;
                    }
                }

                return new RandomIntegerLocal();
            } // End of getRandomInteger() method
        }

        public class Main
        {
            public static void main( String[] args ) {

                LocalGen local = new LocalGen();
                IntGenerator rLocal = local.getRandomInteger();
                System.out.println( rLocal.getValue() );
                System.out.println( rLocal.getValue() );
            }
        }

    The code above generates the following result.
        230737431
        162568032


    Anonymous Inner Class

    An anonymous inner class does not have a name.
    Since it does not have a name, it cannot have a constructor.

    An anonymous class is a one-time class.
    You define an anonymous class and create its object at the same time.

    The general syntax for creating an anonymous class and its object is as follows:

        new Interface()
        {
            // Anonymous  class body  goes  here
        }

        and

        new Superclass(<argument-list-for-a-superclass-constructor>)
        {
            // Anonymous  class body  goes  here
        }

    The new operator is used to create an instance of the anonymous class.
    It is followed by either an existing interface name or an existing class name.

    The interface name or class name is not the name for the newly created anonymous class.
    If an interface name is used, the anonymous class implements the interface.

    If a class name is used, the anonymous class inherits from the class.

    The <argument-list> is used only if the new operator is followed by a class name.
    It is left empty if the new operator is followed by an interface name.

    If <argument-list> is present,
    it contains the actual parameter list for a constructor of the existing class to be invoked.

    The anonymous class body is written as usual inside braces.
    The anonymous class body should be short for better readability.

    The following code contains a simple anonymous class, which prints a message on the standard output.

        public class Main

            public static void main( String[] args ) {

                new Object()
                {
                    // An instance initializer
                    {
                        System.out.println("Hello from an anonymous class.");
                    }
                }; // A semi-colon is necessary to end the statement
            }
        }

    The code above generates the following result.
        Hello from an anonymous class


    Example 2

    The following code use an anonymous class to create an Iterator.

        import java.util.ArrayList;
        import java.util.Iterator;

        public class Main
        {
            private ArrayList<String> titleList = new ArrayList<>();

            public void addTitle( String title ) {
                titleList.add( title );
            }

            public void removeTitle( String title ) {
                titleList.remove( title );
            }

            public Iterator<String> titleIterator() {

                // An anonymous class
                Iterator<String> iterator = new Iterator<String>()
                {
                    int count = 0;

                    @Override
                    public boolean hasNext() {
                        return ( count < titleList.size() );
                    }

                    @Override
                    public String next() {
                        return titleList.get( count++ );
                    }
                }; // Anonymous inner class ends here

                return iterator;
            }
        }
 */

public class InnerClassesTypes
{
}
