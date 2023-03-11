package Creation;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Constructors

    A constructor is a block of code used to initialize an object immediately after the object is created.
    The structure of a constructor looks similar to a method.


    Declaring a Constructor

    The general syntax for a constructor declaration is

        <Modifiers> <Constructor Name>(<parameters list>) throws <Exceptions list> {
        }

    The declaration of a constructor starts with modifiers.

    A constructor can have its access modifier as public, private, protected, or package-level (no modifier).

    The constructor name is the same as the simple name of the class.

    The constructor name is followed by a pair of parentheses, which may include parameters.

    Optionally, the closing parenthesis may be followed by the keyword throws,
    which in turn is followed by a comma-separated list of exceptions.

    The following code shows an example of declaring a constructor for a class Test.
    Name of the class and name of constructor must match.

    public class Test
    {
        public Test() {
            // Code goes here
        }
    }

    Unlike a method, a constructor does not have a return type.


    Use a Constructor

    We use a constructor with the new operator to initialize an instance of a class just after the new instance is created.

    The new operator creates an object and a constructor initializes the object.

    The following statement uses a constructor of the Test class to initialize an object of the Test class:

        Test t = new Test();

    The following code shows how to use a Constructor

        class Cat
        {
            public Cat() {
                System.out.println("in constructor...");
            }
        }

        public class Main
        {
            public static void main( String[] args ) {
                // Create a Cat object and ignore its reference
                new Cat();
                // Create another Cat object and store its reference in c
                Cat c = new Cat();
            }
        }

    The code above generates the following result.
        in constructor...
        in constructor...


    Overloading a Constructor

    A class can have more than one constructor. They are called overloaded constructors.

    If a class has multiple constructors,
    all of them must differ from the others in the number, order, or type of parameters.

    The following code declares two constructors.
    One constructor accepts no parameters and another accepts a String parameter.

        class Car
        {
            // Constructor #1
            public Car() {
                System.out.println( "A car is created." );
            }

            // Constructor #2
            public Car( String name ) {
                System.out.println( "A car named " + name + " is created." );
            }
        }

        public class Main
        {
            public static void main( String[] args ) {

                Car d1 = new Car(); // Uses Constructor #1
                Car d2 = new Car( "My Car" ); // Uses Constructor #2
            }
        }

    The code above generates the following result.
        A car is created.
        A car named My Car is created.

    A constructor is called once per object creation expression.
    We can execute the code for one constructor only once in the process of an object creation.


    Calling a Constructor from another Constructor

    A constructor may call another constructor of the same class.
    Let's consider the following Test class.

    It declares two constructors; one accepts no parameters and one accepts an int parameter.
    We must use the keyword this to call a constructor from another constructor.

    The following code calls the constructor with an int parameter from the constructor
    with no parameter using the statement, "this( 1 );".

        class Test
        {
            Test() {
                this( 1 ); // OK. Note the use of the keyword this.
            }

            Test( int x ) {
            }
        }

    If a constructor calls another constructor, it must be the first executable statement in the constructor's body.
    A constructor cannot call itself because it will result in a recursive call.


    return from a Constructor

    A constructor cannot have a return type in its declaration.
    We can use a return statement without a return expression inside a constructor body.

    When a return statement in a constructor is executed, the control returns to the caller,
    ignoring the rest of the constructor's code.

    The following code shows an example of using a return statement in a constructor.

        class Test
        {
            public Test( int x ) {
                if ( x < 0 ) {
                    return;
                }
                System.out.println( "here" );
            }
        }


    Access Level Modifier for a Constructor

    Access level for a constructor determines the program that can use that constructor in an object creation expression.

    We can specify one of the four access levels for a constructor:
        public, private, protected, and package-level.

    The following code declares four constructors for the Test class.

        // Class Test   has  public access level
        public class Test
        {
            // Constructor #1 - Package-level access
            Test() {
            }

            // Constructor #2 - public access level
            public Test( int x ) {
            }

            // Constructor #3 - private access level
            private Test( int x, int y ) {
            }

            // Constructor #4 - protected access level
            protected Test( int x, int y, int z ) {
            }
        }

    A constructor with a public access level can be used in any part of the program.

    A constructor with private access level can be used only inside the same class in which it is declared.

    A constructor with protected access level can be used in the program with the same package in which its
    class is declared and inside any descendant class in any package.

    A constructor with package-level access can be used inside the same package in which its class is declared.


    Default Constructor

    Java compiler adds a constructor to class if we do not declare one.
    The constructor that is added by the compiler is called the default constructor.

    The default constructor does not have any parameters.
    The default constructor is also called a no-args constructor.

    If the class already had a constructor, the compiler does not add any constructor.
 */

public class Constructors {

    // Constructor #1 - Package-level access
    Constructors() {
        this( 1 ); // call Constructors( int x ) method
    }

    // Constructor #2 - public access level
    public Constructors( int x ) {
    }

    // Constructor #3 - private access level
    private Constructors( int x, int y ) {
    }

    // Constructor #4 - protected access level
    protected Constructors( int x, int y, int z ) {
    }
}
