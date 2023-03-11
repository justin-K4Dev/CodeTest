package Interface;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Interface Fields

    An interface can have three types of members:

        * Constant fields
        * Abstract, static, and default methods
        * Static types as nested interfaces and classes

    An interface cannot have mutable instance and class variables.
    Unlike a class, an interface cannot be instantiated.
    All members of an interface are implicitly public.


    Constant Fields Declarations

    We can declare constant fields in an interface as follows.
    It declares an interface named Choices, which has declarations of two fields:
        YES and NO. Both are of int data type.

        public interface Choices
        {
            public static final int YES = 1;
            public static final int NO = 2;
        }

    All fields in an interface are implicitly public, static, and final.
    The Choices interface can be declared as follows without changing its meaning:

        public interface Choices {
            int YES  = 1;
            int NO  = 2;
        }

    You can access the fields in an interface using the dot notation in the form of

        <interface-name>.<field-name>

    You can use Choices.YES and Choices.NO to access the values of YES and NO fields in the Choices interface.

    The following code demonstrates how to use the dot notation to access fields of an interface.

        public class ChoicesTest {
            public static void main( String[] args ) {
                System.out.println( "Choices.YES = " + Choices.YES );
                System.out.println( "Choices.NO = " + Choices.NO );
            }
        }

    Fields in an interface are always final whether the keyword final is used in its declaration or not.
    We must initialize a field at the time of declaration.

    We can initialize a field with a compile-time or runtime constant expression.
    Since a final field is assigned a value only once, we cannot set the value of the field of an interface,
    except in its declaration.

    The following code shows some valid and invalid field declarations for an interface:

        public interface ValidFields
        {
            int X = 10;
            int Y = X;
            double N = X + 10.5;

            boolean YES = true;
            boolean NO = false;

            Test TEST = new Test();
        }

    It is a convention to use all uppercase letters in the name of a field in an interface to indicate
    that they are constants.

    The fields of an interface are always public.
 */

public class InterfaceFields {
}
