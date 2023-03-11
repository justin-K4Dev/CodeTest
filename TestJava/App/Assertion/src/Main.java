/**
 * Created by justin on 2015-06-08.
 */

import java.util.Scanner;
import java.io.*;

import Basic.Assertion;

public class Main {

    public static void main( String[] args ) {

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
