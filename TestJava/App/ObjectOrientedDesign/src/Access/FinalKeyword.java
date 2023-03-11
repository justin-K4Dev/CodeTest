package Access;

/**
 * Created by justin on 2015-08-10.
 */

/*
    final Keyword

    The final keyword does not allow modifying or replacing its original value or definition.

    The final keyword can be used in the following three contexts:
        * A variable declaration
        * A class declaration
        * A method declaration


    final variable

    If a variable is declared final, it can be assigned a value only once.
    The value of a final variable cannot be modified once it has been set.

    A variable declaration includes the declaration of a local variable,
    a formal parameter of a method/constructor, an instance variable, and a class variable.

    To declare a variable as final, use the final keyword in the variable's declaration.

        final int YES  = 1;

    We can set the value of a final variable only once.

    There are two ways to initialize a final variable:

    initialize it at the time of its declaration.
    defer its initialization until a later time.
    However, we must initialize the final variable before it is read for the first time.

        * final Local Variables
          You can declare a local variable final.
          If you declare a local variable as a blank final variable, you must initialize it before using.

        * final Parameters
          We can declare a parameter final. A parameter is initialized automatically
          with the value of the actual parameter when the method or the constructor is invoked.

          Therefore, you cannot change the value of a final formal parameter inside the method's
          or the constructor's body.

        * final Instance Variables
          We can declare an instance variable final and blank final.

          A blank final instance variable must be initialized once
          and only once when any of the constructors of the class is invoked.

        * final Class Variables
          We can declare a class variable final and blank final.
          We must initialize a blank final class variable in one of the static initializers.

        * final Reference Variables
          A reference variable stores the reference of an object.
          A final reference variable means that once it references an object (or null),
          it cannot be modified to reference another object.

    The following code shows the final formal parameter x for the test2() method:

        public void  test2( final int x )  {

    If we have more than one static initializer for a class,
    we must initialize all the blank final class variables only once in one of the static initializers.

        public class Main {
            public static final int YES = 1;
            public static final int NO = 2;
            public static final String MSG;

            static {
                MSG = "final static variable";
            }
        }


    final class

    If a class is declared final, it cannot be extended (or subclassed).


    final method

    If a method is declared final,
    it cannot be redefined (overridden or hidden) in the subclasses of the class that contains the method.
 */


public class FinalKeyword {
}
