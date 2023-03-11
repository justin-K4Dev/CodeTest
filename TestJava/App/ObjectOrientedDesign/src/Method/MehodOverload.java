package Method;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Method Overload

    Having more than one method with the same name in the same class is called method overloading.

    Methods with the same name in a class could be declared methods, inherited methods, or a combination of both.

    Overloaded methods must have different number of parameters, different types of parameters, or both.

    The return type, access level and throws clause of a method play no effect in making it an overloaded method.

    import java.io.IOException;

    class MyClass
    {
        public void m1( int a ) {
            // Code goes here
        }

        public void m1( int a, int b ) {
            // Code goes here
        }

        public int m1( String a ) {
            // Code goes here
            return 0;
        }

        public int m1( String a, int b ) throws IOException {
            // Code goes here
            return 0;
        }
    }
 */

public class MehodOverload
{
    public double add( int a, int b ) {
        System.out.println( "Inside add( int a, int b )" );
        double s = a + b;
        return s;
    }

    public double add( double a, double b ) {
        System.out.println( "Inside add( double a,  double b )" );
        double s = a + b;
        return s;
    }

    public static void Test1() {

        MehodOverload ot = new MehodOverload();

        int i = 1;
        int j = 1;
        double d1 = 10.42;
        float f1 = 22.3F;
        float f2 = 24.5F;
        short s1 = 22;
        short s2 = 26;

        ot.add( i, j );
        ot.add( d1, j );
        ot.add( i, s1 );
        ot.add( s1, s2 );
        ot.add( f1, f2 );
        ot.add( f1, s2 );
    }
    // The code above generates the following result.
        // Inside add( int a, int b )
        // Inside add( double a, double b )
        // Inside add( int a, int b )
        // Inside add( int a, int b )
        // Inside add( double a, double b )
        // Inside add( double a, double b )

    public static void Test2() {

        /*
            Sometimes, overloaded methods and automatic type
            widening may confuse the compiler resulting in a compiler error.
         */

        Adder a = new Adder();

        // double d = a.add( 2, 3 ); // A compile-time error
        double d1 = a.add( (double) 2, 3 ); // OK. Will use add( double, int )
        double d2 = a.add( 2, (double) 3 ); // OK. Will use add( int, double )
    }
}

class Adder
{
    public double add( int a, double b ) {
        return a + b;
    }

    public double add( double a, int b ) {
        return a + b;
    }
}
