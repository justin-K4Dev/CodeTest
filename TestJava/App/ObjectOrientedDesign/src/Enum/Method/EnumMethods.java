/**
 * Created by justin on 2015-07-16.
 */

package Enum.Method;

/*
    Enum Methods

    Since an enum type is actually a class type,
    we can declare everything inside an enum type body that we can declare inside a class body.

    The following code defines a Level enum with fields, constructors, and methods

        public enum Level {
            LOW(30), MEDIUM(15), HIGH(7), URGENT(1);

            // Declare an instance variable
            private int levelValue;

            // Declare a private constructor
            private Level( int levelValue ) {
                this.levelValue = levelValue;
            }

            public int getLevelValue() {
                return levelValue;
            }
        }

    The code above declares an instance variable levelValue, which will store a value for each enum constant.

    It also defines a private constructor, which accepts an int parameter.
    It stores the value of its parameter in the instance variable.

    We can add multiple constructors to an enum type.

    We cannot add a public or protected constructor to an enum type.

    Level enum declares a public method getLevelValue().

    The enum constant declarations have changed to
        LOW(30), MEDIUM(15),  HIGH(7),  URGENT(1);

    Now every enum constant name is followed by an integer value in parentheses.
    LOW(30) is shorthand for calling the constructor with an int parameter type.

    When an enum constant is created, the value inside the parentheses will be passed to the constructor
    that we have added.

    LOW invokes a default no-args constructor, while LOW(30) calls the constructor with parameter.

    The following code tests the Level enum type. It prints the names of the constants,
    their ordinals, and their underline value.
 */

enum Level
{
    LOW( 30 ), MEDIUM( 15 ), HIGH( 7 ), URGENT( 1 );

    // Declare an instance variable
    private int levelValue;

    // Declare a private constructor
    private Level(int levelValue) {
        this.levelValue = levelValue;
    }

    public int GetLevelValue() {
        return levelValue;
    }
}

public class EnumMethods
{
    public static void Test() {
        for ( Level s : Level.values() ) {
            String name = s.name();
            int ordinal = s.ordinal();
            int underLine = s.GetLevelValue();
            System.out.println( "name = " + name + ",  ordinal = " + ordinal + ", underLine = " + underLine );
        }
    }
    // The code above generates the following result.
        // name = LOW, ordinal = 0, underLine = 30
        // name = MEDIUM, ordinal = 1, underLine = 15
        // name = HIGH, ordinal = 2, underLine = 7
        // name = URGENT, ordinal = 3, underLine = 1
}
