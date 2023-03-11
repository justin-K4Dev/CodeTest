

/**
 * Created by justin on 2015-07-16.
 */

package Enum.Value;

/*
    Enum Value

    An enum type defines two things:

        * The enum constants
        * The order for those constants

    The following code declares a public enum type called ItemLevel with four enum constants:
    LOW, MEDIUM, HIGH, and URGENT.

        public enum Level {
            LOW,  MEDIUM,  HIGH, URGENT;
        }

    The Level enum type defines four enum constants.

    A variable of the Level enum type can have only one of the four values-LOW, MEDIUM, HIGH, and URGENT-or null.

    We can use dot notation to refer to the enum constants by using the enum type name as the qualifier.

    The following code assigns values to a variable of Level enum type:

        Level low  = Level.LOW;
        Level medium = Level.MEDIUM;
        Level high  = Level.HIGH;
        Level urgent = Level.URGENT;

    We cannot instantiate an enum type. The following code results in a compile-time error:

        Level badAttempt = new Level(); // A compile-time error
 */