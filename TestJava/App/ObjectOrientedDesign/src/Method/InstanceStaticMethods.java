package Method;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Instance / Static Methods

    A class can have two types of methods: instance methods and class methods.
    Instance methods and class methods are also called non-static methods and static methods, respectively.

    An instance method is used to implement behavior for the instances of the class.
    An instance method can only be invoked in the context of an instance of the class.

    A class method is used to implement the behavior for the class itself.
    A class method always executes in the context of a class.

    The static modifier is used to define a class method.
    The absence of the static modifier in a method declaration makes the method an instance method.


    Example

    The following are examples of declaring some static and non-static methods:

        // A static or class method
        static void aClassMethod() {

        }

        // A non-static or instance method
        void  anInstanceMethod() {

        }

    Note

    When a static method of a class is called, an instance of that class may not exist.
    Therefore, it is not allowed to refer to instance variables from inside a static method.

    Class variables exist as soon as the class definition is loaded into memory.
    The class definition is loaded into memory before the first instance of a class is created.

    A class method or static method can refer to only class variables or static variables of the class.
    An instance method or non-static method can refer to class variables as well as instance variables of the class.

    The following code demonstrate the types of class fields that are accessible inside a method.

        public class Main
        {
            static int m = 100; // A static variable
            int n = 200; // An instance variable

            // Declare a static method
            static void printM() {

                // We can refer to only static variable m in this method because you are
                // inside a static method
                System.out.println("printM() - m   = " + m);
            }

            // Declare an instance method
            void printMN() {
                // We can refer to both static and instance variables m and n in this method
                System.out.println( "printMN() - m = " + m );
                System.out.println( "printMN() - n = " + n );
            }
        }


    Invoking a Method

    Executing the code in the body of a method is called invoking (or calling) a method.

    Instance methods and class methods are invoked differently.

    An instance method is invoked on an instance of the class using dot notation.

        <instance reference>.<instance method name>(<actual parameters>)

    We must have a reference to an instance of a class before calling an instance method of that class.

    The following code shows how to invoke the printMN() instance method of the Main class:

        // Create an instance of InstanceStaticMethods class and
        // store its reference in ism reference variable
        InstanceStaticMethods ism = new InstanceStaticMethods();

        // Invoke the printMN() instance method using the ism reference variable
        ism.printMN();
        To invoke a class method, use dot notation with the class name.

    The following code invokes the printM() class method of the InstanceStaticMethods class:

        // Invoke the printM() class method
        InstanceStaticMethods.printM();

    Whatever belongs to a class also belongs to all instances of that class.
    We can also invoke a class method using a reference of an instance of that class.

        InstanceStaticMethods ism = new InstanceStaticMethods();
        ism.printM(); // Call the class method  using an instance ism

    Using the class name to invoke a class method is more intuitive than using an instance reference.
 */

public class InstanceStaticMethods {
}