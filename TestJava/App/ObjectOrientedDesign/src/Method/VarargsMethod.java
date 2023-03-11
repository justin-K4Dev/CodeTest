package Method;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Varargs Method

    The term "varargs" is shorthand for "variable-length arguments."

    The varargs declares a method or constructor that accepts a variable number of arguments (or parameters).

    Declare varargs Method

    To declare varargs, add an ellipsis ... after the data type of the method's argument.

    The following code shows a max() method declaration with one variable-length argument, num, which is of the int data type.

        public static int max( int... num ) {

        }

    Adding whitespaces before and after ellipsis is optional.

    A varargs method can have more than one argument.
    The following code shows that aMethod() accepts three arguments, one of which is a variable-length argument:

        public static int aMethod( String str, double d1, int...num )  {

        }

    A varargs method can have a maximum of one variable-length argument.

    The variable-length argument of a varargs method must be the last argument in the argument list.

        void  m2( String str, int...n1 ) {

        }


    Use varargs Method

    We can use a for loop to process the list of arguments for the variable-length argument.

    The length property gives you the number of values that were passed for the variable-length argument.

    To get the nth value in the variable-length argument, you need to use varArgsName[n-1].

    We can use a foreach loop to work with variable-length argument.
        The following code shows a max2() method

    We can call the Main.max() method as follows:

        int max1 = VarargsMethod.max1( 1, 8 );
        int max2 = VarargsMethod.max1( 1, 1, 3 );

    You can use zero or more arguments for a variable-length argument in a method.
    The following code is a valid call to the max() method:

        int max = VarargsMethod.max1(); // Passing no argument is ok

    The following declaration of the max() method will force its caller to pass at least two integers:

        // Argumenets n1 and n2 are mandatory
        public static int max( int n1, int n2, int... num ) {

        }

    The compiler will treat the first two arguments, n1 and n2, as mandatory and the third argument, num, as optional.
        The following code shows a max3() method


    Overloading a Varargs Method

    The same overloading rules for methods apply to a varargs method.

    We can overload a method with a variable-length argument as long as the parameters for
    the methods differ in type, order, or number.

    For example, the following is a valid example of an overloaded max() method:

        public class Main
        {
            public static int max( int x, int y )  {
            }

            public static int max( int...num )  {
            }
        }

    Consider the following code

        int max = Main.max( 12, 13 );  // which  max()  will be  called ?

    Java will call the max( int x, int y ).
    Java first attempts to find a method declaration using an exact match for the number of parameters.
    If it does not find an exact match, it looks for a match using variable-length parameters.

    If a varargs method is overloaded,
    Java uses the more specific version of the method instead of using a varargs method.
    java uses varargs method as the last resort to resolve a method call.

    The overloading of the method itself may be valid.
    However, the call to it may cause an issue.

        public class Main
        {
            public static int max( int... num ) {
                return 0;
            }

            public static int max( double... num ) {
                return 0;
            }
        }

    Which max() would the following code call ?

        int max = Main.max(); // Which max()  to call?

    The above statement will generate a compilation time error.


    Varargs Methods and the main() Method

    The signature for the main() method must be main( String[] args ).

    The following declaration of main() method for the Main class is valid.

        public class Main
        {
            public static void main( String... args ) {
                System.out.println( "Hello from  varargs main()..." );
            }
        }
 */

public class VarargsMethod
{
    // Let's rewrite the max() method to make it a varargs method:
    public static int max1( int... num ) {
        int max = Integer.MIN_VALUE;
        for ( int i = 0; i < num.length; i++ ) {
            if ( num[i] > max ) {
                max = num[i];
            }
        }
        return max;
    }

    public static int max2( int... num ) {
        int max = Integer.MIN_VALUE;

        // foreach loop use
        for ( int currentNumber : num ) {
            if ( currentNumber > max ) {
                max = currentNumber;
            }
        }
        return max;
    }

    public static int max3( int n1, int n2, int... num ) {
        // Initialize max to the maximum of n1 and n2
        int max = ( n1 > n2 ? n1 : n2 );

        for ( int i = 0; i < num.length; i++ ) {
            if ( num[i] > max ) {
                max = num[i];
            }
        }
        return max;
    }

    public static void Test() {
        System.out.println( max3( 7, 9 ) );
        System.out.println( max3( 7, 9, 10 ) );
        System.out.println( max3( 7, 9, 10, 13 ) );
    }
    // The code above generates the following result.
        // 9
        // 10
        // 13
}
