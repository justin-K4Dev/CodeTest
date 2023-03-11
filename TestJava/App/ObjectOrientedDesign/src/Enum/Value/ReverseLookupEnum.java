/**
 * Created by justin on 2015-07-16.
 */

package Enum.Value;

/*
    Reverse Lookup for Enum Constants

    We can get the reference of an enum constant from its name or position. using valueOf() method.

    The reverse lookup for enum constants is case-sensitive.

    We can use the array returned by the values() method to perform reverse lookup by ordinal.

    The order of the values in the array returned by values() method is the same as
    the order in which the enum constants are declared.

    The ordinal of enum constants starts at zero.

    The following code demonstrates how to reverse look up enum constants:
 */

enum OptionLevel
{
    LOW, MEDIUM, HIGH, URGENT;
}

public class ReverseLookupEnum
{
    public static void Test() {

        // reverse lookup using a name
        OptionLevel low1 = OptionLevel.valueOf( "LOW" );
        // reverse lookup using an ordinal
        OptionLevel low2 = OptionLevel.values()[0];

        System.out.println( low1 );
        System.out.println( low2 );
        System.out.println( low1 == low2 );
    }
    // The code above generates the following result.
        // LOW
        // LOW
        // true
}
