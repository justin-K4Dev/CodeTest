/**
 * Created by justin on 2015-07-16.
 */

package Enum.Value;

/*
    Enum order number

    An enum type assigns an order number, called ordinal, to all of its constants.

    The ordinal starts with zero and is incremented by one as moving from first to last in the list of constants.

    The first enum constant is assigned the value of zero, the second of 1, the third of 2, and so on.

    The ordinal values assigned to constants declared in Level enum type are
    0 to LOW, 1 to MEDIUM, 2 to HIGH, and 3 to URGENT.

    Each enum constant has a name which is the same as the identifier for the constant.
    For example, the name for the LOW constant in the Level enum type is "LOW".

    We can get the name and the ordinal of an enum constant using the name() and ordinal() methods, respectively.

    Each enum type has a static method named values() that returns an array of constants in the order
    they are declared in its body.

    The following code prints the name and ordinal of all enum constants declared in the Level enum type.
 */

enum Level
{
    LOW, MEDIUM, HIGH, URGENT;
}

public class OrderNumberEnum {

    public static void Test() {

        for ( Level s : Level.values() ) {
            String name = s.name();
            int ordinal = s.ordinal();

            System.out.println( name + "(" + ordinal + ")" );
        }
    }
    // The code above generates the following result.
        // LOW(0)
        // MEDIUM(1)
        // HIGH(2)
        // URGENT(3)
}
