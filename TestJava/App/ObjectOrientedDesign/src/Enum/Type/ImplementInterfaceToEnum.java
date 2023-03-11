/**
 * Created by justin on 2015-07-16.
 */

package Enum.Type;

/*
    Implementing an Interface to an Enum Type

    An enum type may implement interfaces.
    The rules for an enum type implementing an interface are the same as the rules
    for a class implementing an interface.

    The following code shows how to let enum type implement an interface.
 */

interface Command
{
    void Execute();
}

enum Level implements Command
{
    LOW {
        public void Execute() {
            System.out.println( "Low..." );
        }
    },
    HIGH {
        public void Execute() {
            System.out.println( "High..." );
        }
    };

    public abstract void Execute();
}

public class ImplementInterfaceToEnum
{
    public static void Test() {

        for ( Command cmd : Level.values() ) {
            cmd.Execute();
        }
    }
    // The code above generates the following result.
        // Low...
        // High...
}
