/**
 * Created by justin on 2015-07-16.
 */

package Enum.DataType;

/*
    Adding bodies to an Enum Constant

    We can add a different body to each enum constant.
    The body can have fields and methods.

    The body for an enum constant is placed inside braces following its name.

    If the enum constant accepts arguments, its body follows its argument list.
    The syntax for associating a body to an enum constant is as follows:

        <access-modifier> enum <enum-type-name> {
            ENUM_VALUE1  {
                // Body for ENUM_VALUE1 goes here
            },
            ENUM_VALUE2  {
                // Body for ENUM_VALUE2 goes here
            },
            ENUM_VALUE3( arguments-list )  {
                // Body of ENUM_VALUE3 goes here
            };
            // Other  code  goes  here
        }

    The following code creates Level enum type with body.

    Level enum has an abstract method getDistance().
    Each instance constant has a body that provides implementation for the getDistance() method.
    It has overridden the toString() method in the Enum class.
 */

enum Level
{
    LOW( "Low Level", 30 ) {
        public double GetDistance() {
            return 30.0;
        }
    },
    MEDIUM( "Medium Level", 15 ) {
        public double GetDistance() {
            return 15.0;
        }
    },
    HIGH( "High Level", 7 ) {
        public double GetDistance() {
            return 7.0;
        }
    },
    URGENT( "Urgent Level", 1 ) {
        public double GetDistance() {
            return 1.0;
        }
    };

    private int levelValue;
    private String description;

    private Level( String description, int levelValue ) {
        this.description = description;
        this.levelValue = levelValue;
    }

    public int GetLevelValue() {
        return levelValue;
    }

    public String ToString() {
        return this.description;
    }

    public abstract double GetDistance();
}

public class EnumAddBody
{
    public static void Test() {

        for ( Level s : Level.values() ) {

            String name = s.name();
            String desc = s.ToString();
            int ordinal = s.ordinal();

            int levelValue = s.GetLevelValue();
            double distance = s.GetDistance();

            System.out.println( "name = " + name + ", description = " + desc + ", ordinal = " + ordinal + ", levelValue = " + levelValue + ", distance = " + distance );
        }
    }
    // The code above generates the following result.
        // name = LOW, description = Low Level, ordinal = 0, levelValue = 30, distance = 30.0
        // name = MEDIUM, description = Medium Level, ordinal = 1, levelValue = 15, distance = 15.0
        // name = HIGH, description = High Level, ordinal = 2, levelValue = 7, distance = 7.0
        // name = URGENT, description = Urgent Level, ordinal = 3, levelValue = 1, distance = 1.0
}
