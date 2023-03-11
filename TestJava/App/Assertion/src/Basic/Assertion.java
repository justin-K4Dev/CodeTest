package Basic;

/**
 * Created by justin on 2015-06-08.
 */
public class Assertion {

    public static boolean NDEBUG = true;

    private static void PrintStack( String why ) {

        Throwable t = new Throwable( why );
        t.printStackTrace();

        System.exit( 1 );
    }

    public static void Assert( boolean expression, String why ) {

        if ( NDEBUG && !expression ) {
            Assertion.PrintStack( why );
        }
    }
}
