/**
 * Created by justin on 2015-07-16.
 */

package Enum.Value;

/*
    Range of Enum Constants

    java.util.EnumSet collection class works with lists of enum constants of an enum type.

    The following code demonstrates how to use the EnumSet class to work with the range for enum constants.
 */

import java.util.EnumSet;

enum ObjectLevel
{
    LOW, MEDIUM, HIGH, URGENT;
}

public class RangeEnum
{
    public static void Test() {

        EnumSet<ObjectLevel> allLevels = EnumSet.allOf( ObjectLevel.class );
        Print( allLevels );

        EnumSet<ObjectLevel> l = EnumSet.range( ObjectLevel.LOW, ObjectLevel.URGENT );
        Print( l );
    }
    // The code above generates the following result.
        // LOW
        // MEDIUM
        // HIGH
        // URGENT
        // LOW
        // MEDIUM
        // HIGH
        // URGENT

    public static void Print( EnumSet<ObjectLevel> levels ) {
        for ( ObjectLevel d : levels ) {
            System.out.println( d + " " );
        }
    }
}
