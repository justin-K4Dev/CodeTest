/**
 * Created by justin on 2015-07-15.
 */

package Enum.Type;

/*
    Enum Types

    What Is an Enum Type ?

    An enum type creates an ordered list of constants as a type.
    It specifies constants in a specific order.

    The constants defined in an enum type are instances of that enum type.


    Syntax

    You define an enum type using the keyword enum with the following syntax:

        <access-modifier> enum <enum-type-name>
        {
            // List of  comma  separated names of  enum constants
        }

    <access-modifiers> is the same as the access modifier for a class:
        public, private, protected, or package-level.

    <enum-type-name> is a valid Java identifier.

    The body of the enum type is placed within braces following its name,
    The body can have a list of comma-separated constants and other elements,
    for example, instance variables, methods, etc.

    Most of the time, the enum body includes only constants.


    Example

    The following code declares an enum type called Gender, which declares two constants, MALE and FEMALE:

        public enum Gender {
            MALE,  FEMALE;  // The semi-colon is optional
        }

    It is a convention to name the enum constants in uppercase.
    The following code declares a public enum type called Level with four enum constants:
        LOW, MEDIUM, HIGH, and URGENT.

        public enum Level {
            LOW,  MEDIUM,  HIGH, URGENT;
        }

    A public enum type can be accessed from anywhere in the application.

    A public enum type stays in a file with enum type name.
    The Level enum would be saved in a file named Level.java.

    We need to place an enum type in a package and we can use an import statement to import an enum type.


    enum variable

    We can declare a variable of an enum type the same way we declare a variable of a class type.
    The following code declare errorLevel variable of the Level enum type

        Level errorLevel;

    You can assign null to an enum type variable, like so:

        Level defectLevel = null;
 */

enum Direction
{
    East, South, West, North
}

public class EnumType
{
    public static void Test() {

        /*
            Using Enum Types in switch Statements

            You can use enum types in switch statements.
            When the switch expression is of an enum type,
            all case labels must be unqualified enum constants of the same enum type.
        */
        Direction dir = Direction.South;
        switch ( dir ) {
            case South:
                System.out.println( "South" );
                break;
            case East:
                System.out.println( "East" );
                break;
            case West:
                System.out.println( "West" );
                break;
            case North:
                System.out.println( "North" );
                break;
        }
    }
    // The code above generates the following result.
        // South
}
