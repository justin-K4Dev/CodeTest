/**
 * Created by justin on 2015-07-16.
 */

package Enum.Type;

/*
    Nested Enum Types

    We can have a nested enum type declaration inside a class, an interface, or another enum type.

    Nested enum types are implicitly static.
    Since an enum type is always static, we cannot declare a local enum type inside a method's body.

    We can use any of the access modifiers (public, private, protected, or package) level for a nested enum type.

    The following code shows how to declare a nested public enum type named Gender inside a Person class.

    The Person.Gender enum type can be accessed from anywhere in the application because it has been declared public.

    We can also use the simple name of an enum constant by importing the enum constants using static imports.

        import static  Enum.Type.Person.Gender.*;
 */

class Person
{
    public enum Gender {
        MALE, FEMALE
    }
}

public class NestedEnum {

    public static void Test() {

        Person.Gender m = Person.Gender.MALE;
        Person.Gender f = Person.Gender.FEMALE;

        System.out.println( m );
        System.out.println( f );
    }
}

