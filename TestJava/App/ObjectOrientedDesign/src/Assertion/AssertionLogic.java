package Assertion;

import java.util.Scanner;

/**
 * Created by justin on 2015-08-13.
 */

class Assertion {

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

public class AssertionLogic {

    public static void Test() {

        //Assertion.NDEBUG = false;

        // Assertion 3 test
        {
            Scanner reader = new Scanner( System.in );
            System.out.print( "Enter your marital status: " );

            char value = reader.next().charAt(0);
            System.out.println("Input value : " + value );

            switch ( value ) {
                case 's':
                case 'S': { System.out.println("Single"); } break;

                case 'm':
                case 'M': { System.out.println("Married"); } break;

                case 'd':
                case 'D': { System.out.println("Divorced"); } break;

                default: { assert !true : "Invalid Option"; } break; // set vm option : -ea
            }
        }

        // Assertion 2 test
        {
            Scanner reader = new Scanner( System.in );
            System.out.print( "Enter your marital status: " );

            char value = reader.next().charAt(0);
            System.out.println("Input value : " + value );

            switch ( value ) {
                case 's':
                case 'S': { System.out.println("Single"); } break;

                case 'm':
                case 'M': { System.out.println("Married"); } break;

                case 'd':
                case 'D': { System.out.println("Divorced"); } break;

                default: { Assertion.Assert( !true, "Invalid Option" ); } break;
            }
        }

        // Assertion 1 test
        {
            Scanner reader = new Scanner( System.in );
            System.out.print("Enter your age: ");

            int age = reader.nextInt();
            Assertion.Assert(age >= 18, "You are too young to vote");

            // use age
            System.out.println("You are eligible to vote");
        }
    }
}