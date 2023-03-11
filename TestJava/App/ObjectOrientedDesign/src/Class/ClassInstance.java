package Class;

/**
 * Created by justin on 2015-08-03.
 */

/*
    Class Instance

    The following is the general syntax to create an instance of a class:

        new <Class Constructor>;

    The new operator is followed by a call to the constructor.

    The new operator creates an instance of a class by allocating the memory on heap.
    The following statement creates an instance of the Dog class:

        new Dog();

    Dog() is a call to the constructor of the Dog class.

    When we do not add a constructor to a class, the Java compiler adds one for us.

    The constructor added by the Java compiler is called a default constructor.
    The default constructor accepts no arguments.

    The name of the constructor of a class is the same as the class name.

    The new operator allocates memory for each instance field of the class.
    Class static variables are not allocated memory when an instance of the class is created.

    To access instance variables of an instance of a class, we must have its reference.

    The name of a class defines a new reference type in Java.
    A variable of a specific reference type can store the reference of an instance of the same reference type.

    To declare a reference variable, which will store a reference of an instance of the Dog class.

        Dog anInstance;

    Dog is the class name, which is also a reference type, and anInstance is a variable of that type.

    anInstance is a reference variable of Dog type.
    The anInstance variable can be used to store a reference of an instance of the Dog class.

    The new operator allocates the memory for a new instance of a class and returns the reference to that instance.

    We need to store the reference returned by the new operator in a reference variable.

        anInstance = new Dog();


    null Reference Type

    We can assign a null value to a variable of any reference type.
    A null value means that the reference variable is referring to no object.

        Dog obj = null;  // obj is not referring to any object
        obj = new Dog();  // Now, obj is referring to a valid Dog object

    You can use a null literal with comparison operators to check for equality and inequality.

        if  ( obj == null )  {
            // obj is null
        }

        if  ( obj !=  null )  {
            // obj is not null
        }

    Java does not mix reference types and primitive types.
    We cannot assign null to a primitive type variable.

    Dot Notation to Access Fields of a Class

    Dot notation is used to refer to instance variables.
    The general form of the dot notation syntax is

        <Reference Variable Name>.<Instance Variable Name>

    obj.name to refer to the name instance variable of the instance to which the obj reference variable is referring.

    To assign a value to the name instance variable, use

        obj.name = "Rectangle";

    The following statement assigns the value of the name instance variable to a String variable aName:

        String aName = obj.name;

    To reference class variables, use the name of the class.

        ClassName.ClassVariableName

    For example, we can use Dog.count to refer to the count class variable of the Dog class.

    To assign a new value to the count class variable

        Dog.count = 1;

    To read the value of the count class variable into a variable

        long count = Dog.count;

    The following code shows how to use class fields

        class Dog
        {
            static int count = 0;
            String name;
            String gender;
        }

        public class Main
        {
            public static void main( String[] args ) {

                Dog obj = new Dog();

                // Increase count by one
                Dog.count++;

                obj.name = "Java";
                obj.gender = "Male";

                obj.name = "XML";

                String changedName = obj.name;
            }
        }


    Default Initialization of Fields

    All fields of a class, static as well as non-static, are initialized to a default value.

    The default value of a field depends on its data type.

    A numeric field (byte, short, char, int, long, float, and double) is initialized to zero.
    A boolean field is initialized to false. A reference type field is initialized to null.

    The following code demonstrates the default initialization of fields.
*/

public class ClassInstance {

    byte b;
    short s;
    int i;
    long l;
    float f;
    double d;
    boolean bool;
    String str;

    public static void Test()
    {
        ClassInstance obj = new ClassInstance();

        System.out.println( "byte is initialized to " + obj.l );
        System.out.println( "short is initialized to " + obj.s );
        System.out.println( "int is initialized to " + obj.i );
        System.out.println( "long is initialized to " + obj.l );
        System.out.println( "float is initialized to " + obj.f );
        System.out.println( "double is initialized to " + obj.d );
        System.out.println( "boolean is initialized to " + obj.bool );
        System.out.println( "String is initialized to " + obj.str );
    }
    // The code above generates the following result.
        // byte is initialized to 0
        // short is initialized to 0
        // int is initialized to 0
        // long is initialized to 0
        // float is initialized to 0
        // double is initialized to 0
        // boolean is initialized to false
        // String is initialized to null
}