package Method;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Parameter Passing

    Java supports two kinds of data types: primitive data type and reference data type.

    A primitive data type is a simple data structure and it has only one value associated with it.
    A reference data type is a complex data structure and it represents an object.

    A variable of a primitive data type stores the value directly at its memory address.

    Things are different when you work with objects and reference variables.

    All parameters in Java are passed by value.

    When a parameter is a primitive data type, the value of the actual parameter is copied to the parameter.

    Any changes made to the parameter's value inside the method's body will change only the copy of the formal parameter
    and not the value of the actual parameter.

    When a parameter is passed by reference value,
    the reference stored in the actual parameter is copied to the formal parameter.
    Both the actual parameter and the formal parameter refer to the same object in memory.

    You can assign a reference to another object to the formal parameter inside the method's body.

    The following code demonstrates the pass by reference mechanism in Java.


    Note

    When a reference type parameter is passed to a method,
    the formal parameter can access the object the same way the actual parameter can access the object.

    The formal parameter can modify the object by directly changing the values of the instance variables
    or by calling methods on the object.

    Any modification made on the object through the formal parameter is immediately visible through the actual parameter
    because both hold the reference to the same object in memory.

    The formal parameter itself can be modified to reference another object inside the method.

    To disable the method to change the reference type formal parameter to reference a different object,
    use the keyword final in the reference type formal parameter declaration.
 */

class Phone
{
    public String model = "Unknown";
    public int year = 2014;
    public double price = 0.0;
}

public class ParameterPassing
{
    public static void Test1() {

        {
            Phone myPhone = new Phone();

            myPhone.model = "iPhone";
            myPhone.year = 2009;
            myPhone.price = 16000.0;

            System.out.println( "#1: model = " + myPhone.model + ", year = " + myPhone.year + ", price = " + myPhone.price );

            ParameterPassing.Test2(myPhone);

            System.out.println("#4: model = " + myPhone.model + ", year = " + myPhone.year + ", price = " + myPhone.price);
        }
        // The code above generates the following result.
            // #1 model = iPhone, year = 2009, price = 16000.0
            // #2 model = iPhone, year = 2009, price = 16000.0
            // #3 model = Unknown, year = 2014, price = 0.0
            // #4 model = iPhone, year = 2009, price = 16000.0

        {
            Phone myPhone = new Phone();

            myPhone.model = "iPhone";
            myPhone.year = 2009;
            myPhone.price = 16000.0;

            ParameterPassing.Test3( myPhone );
        }
        // The code above generates the following result.
            // #2 model = iPhone, year = 2009, price = 16000.0
    }

    public static void Test2( Phone xPhone ) {

        System.out.println( "#2: model = " + xPhone.model + ", year = " + xPhone.year + ",  price = " + xPhone.price );

        // Let's make xyCar refer to a new object
        xPhone = new Phone();

        System.out.println( "#3: model = " + xPhone.model + ", year = " + xPhone.year + ", price = " + xPhone.price );
    }

    public static void Test3( final Phone xPhone ) {

        System.out.println( "#2: model = " + xPhone.model + ", year = " + xPhone.year + ",  price = " + xPhone.price );

        // Let's make xyCar refer to a new object
        // xPhone = new Phone();
    }
}
