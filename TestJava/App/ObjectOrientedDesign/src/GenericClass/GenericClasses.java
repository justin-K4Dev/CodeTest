package GenericClass;

/**
 * Created by justin on 2015-08-11.
 */


/*
    Generic Classes

    Using generics, we can write code without knowing the type of the objects the code operates on.
    It lets us create generic classes, constructors, and methods.

    A generic class is defined using formal type parameters.

    Formal type parameters are a list of comma-separated variable names placed in angle-brackets <>
    after the class name in the class declaration.


    Syntax

    The following code declares a class Wrapper that takes one formal type parameter:

        public class Wrapper<T>
        {
        }

    The parameter has been given a name T.

    T is a type variable, which could be any reference type in Java, such as String, Integer, Double, etc.
    The formal type parameter value is specified when the Wrapper class will be used.


    Formal Parameters

    The classes that take formal type parameter are also known as parameterized classes.

    You can declare a variable of the Wrapper class specifying the String type
    as the value for its formal type parameter as shown below.

    Here, String is the actual type parameter.

        Wrapper<String> stringWrapper;

    Java lets us use a generic class without specifying the formal type parameters.


    Usage

    This is allowed for backward compatibility.
    You can also declare a variable of the Wrapper<T> class as shown:

        Wrapper  aRawWrapper;

    When a generic class is used without specifying the actual type parameters, it is known as raw type.
    The above declaration used the Wrapper<T> class as a raw type as it did not specify the value for T.

    The actual type parameter for a generic class must be a reference type.

    Primitive types are not allowed as the actual type parameters for a generic class.

    A class may take more than one formal type parameter.
    The following code declares a Mapper class that takes two formal parameters, T and R:

        public class Mapper<T, R>    {

        }

    We can declare variable of the Mapper<T, R> class as follows:

    Mapper<String, Integer>  mapper;
    Here, the actual type parameters are String and Integer.

    The formal type parameters are available inside the class body to be used as types.

        public class Wrapper<T>
        {
            private T obj;

            public Wrapper( T obj ) {
                this.obj = obj;
            }

            public T get() {
                return obj;
            }

            public void set( T obj ) {
                this.obj = obj;
            }
        }

    The Wrapper<T> class uses the formal type parameter to declare instance variable obj to declare a formal parameter
    for its constructor and set() method, and as a return type for the get() method.

    You can create an object of the generic type by specifying the actual type parameter for the constructor as follows:

        Wrapper<String> w1 = new Wrapper<String>( "Hello" );

    We can omit the actual type parameter.
    In the following code, the compiler will infer the actual type parameter for the constructor as String:

        Wrapper<String> w1 = new Wrapper<>( "Hello" );

    Once you have declared a variable of the generic class, you can think of the formal type parameter
    as the specified actual type parameter for all practical purposes.

    Now, you can think that, for w1, the get() method of the Wrapper class returns a String.

        String s1=  w1.get();


    Example

    The following code shows how to use Wrapper class.

        public class Main
        {
            public static void main( String[] args ) {

                Wrapper<String> w1 = new Wrapper<>( "Hello" );
                String s1 = w1.get();
                System.out.println( "s1=" + s1 );

                w1.set( "Testing generics" );
                String s2 = w1.get();
                System.out.println( "s2=" + s2 );

                w1.set(null);
                String s3 = w1.get();
                System.out.println( "s3=" + s3 );
            }
        }

        class Wrapper<T>
        {
            private T obj;

            public Wrapper( T obj ) {
                this.obj = obj;
            }

            public T get() {
                return obj;
            }

            public void set( T obj ) {
                this.obj = obj;
            }
        }
 */


public class GenericClasses {
}
