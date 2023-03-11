package GenericClass;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Generic Methods and Constructors

    Generic Methods

    We can define type parameters in a method declaration,
    They are specified in angle brackets before the return type of the method.

    The type that contains the generic method declaration does not have to be a generic type.
    We can use the type parameter specified for the generic type inside the non-static method declaration.


    Example

    The following code shows how to define a new type parameter V for method m1().
    The new type parameter V forces the first and the second arguments of method m1() to be of the same type.
    The third argument must be of the same type T, which is the type of the class instantiation.

        class MyBag<T>
        {
            private T ref;

            public MyBag( T ref ) {
                this.ref = ref;
            }

            public T get() {
                return ref;
            }

            public void set( T a ) {
                this.ref = a;
            }
        }

        class Test<T>
        {
            public <V> void m1( MyBag<V> a, MyBag<V> b, T c )  {

            }
        }


    Use Generic Methods

    To pass the actual type parameter for the method's formal type parameter,
    we must specify it in angle brackets <> between the dot and the method name in the method call.

        class MyBag<T>
        {
            private T ref;

            public MyBag( T ref ) {
                this.ref = ref;
            }

            public T get() {
                return ref;
            }

            public void set( T a ) {
                this.ref = a;
            }
        }

        class Test<T>
        {
            public <V> void m1( MyBag<V> a, MyBag<V> b, T c ) {
            }
        }

        public class Main
        {
            public static void main( String[] argv ) {

                Test<String> t = new Test<String>();
                MyBag<Integer> iw1 = new MyBag<Integer>( new Integer( 201 ) );
                MyBag<Integer> iw2 = new MyBag<Integer>( new Integer( 202 ) );

                // Specify that Integer is the actual type for the type parameter for m1()
                t.<Integer>m1( iw1, iw2, "hello" );

                t.m1( iw1, iw2, "hello" );
            }
        }


    Example 2

    The following code shows how to declare a generic static method.
    We cannot refer to the type parameters of the containing class inside the static method.

    A static method can refer only to its own declared type parameters.

    The following static generic type defines a type parameter T,
    which is used to constrain the type of arguments source and dest.

        class MyBag<T>
        {
            private T ref;

            public MyBag( T ref ) {
                this.ref = ref;
            }

            public T get() {
                return ref;
            }

            public void set( T a ) {
                this.ref = a;
            }
        }

        public class Main
        {
            public static <T> void copy ( MyBag<T> source, MyBag<? super T> dest ) {
                T value = source.get();
                dest.set( value );
            }

            public static void main( String[] argv ) {
            }
        }

    To specify the actual type parameter for a static method call, we can do so as follows:

        Main.<Integer>copy( iw1, iw2 );


    Generic Constructor

    We can define type parameters for constructors.

    The following code defines a type parameter U for the constructor of class Test.
    It places a constraint that the constructor's type parameter U must be the same
    or a subtype of the actual type of its class type parameter T.

        public class Test<T>
        {
            public <U extends T> Test( U k ) {
            }
        }

    To specify the actual type parameter value for the constructor,
    specify it in angle brackets between the new operator and the name of the constructor,
    as shown in the following snippet of code:

        class Test<T>
        {
            public <U extends T> Test( U k ) {
            }
        }

        public class Main
        {
            public static void main( String[] argv ) {
                // Specify the actual type parameter for the constructor as Double
                Test<Number> t1 = new<Double> Test<Number>( new Double( 1.9 ) );

                // Let the compiler figure out, Integer is
                // the actual type parameter for the constructor
                Test<Number> t2 = new Test<Number>( new Integer( 1 ) );
            }
        }


    Type Inference in Generic Object Creation

    Java 7 added limited support for type inference in an object-creation expression for generic types.

    For the following statement:

        List<String> list = new ArrayList<String>();

    In Java 7, you can specify empty angle brackets, known as the diamond operator or simply the diamond <>,
    as the type parameter for ArrayList in the above statement.

        List<String> list = new ArrayList<>();

    If we do not specify a type parameter for a generic type in an object-creation expression,
    the type is the raw type and the compiler generates unchecked warnings.

    For example, the following statement will compile with unchecked warnings:

        List<String> list = new ArrayList(); // Generates an  unchecked  warning

    We cannot create generic exception classes. and there is no generic anonymous classes.
*/

public class GenericMethodAndConstructors {
}
