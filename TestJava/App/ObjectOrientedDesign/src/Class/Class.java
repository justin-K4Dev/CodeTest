package Class;

/**
 * Created by justin on 2015-08-03.
 */

/*
    Java Class

    What Is a Class ?

    Classes are the basic units of programming in the object-oriented paradigm.
    They are used as templates to create objects.

    A class in Java may consist of five components:

        * Fields
        * Methods
        * Constructors
        * Static initializers
        * Instance initializers

    Fields and methods are also known as members of the class.

    Classes and interfaces can also be members of a class.

    A class can have zero or more class members.

    Constructors are used to create objects of a class.
    We must have at least one constructor for a class.
    Initializers are used to initialize fields of a class.

    We can have zero or more initializers of static or instance types.


    Declaring a Class

    The general syntax for declaring a class in Java is

        <modifiers> class <class name>
        {
            // Body of the class
        }
        <modifiers> are keywords with special meanings to the class declaration.

    A class declaration may have zero or more modifiers.

    The keyword class is used to declare a class.

    <class name> is a user-defined name for the class, which should be a valid identifier.

    Each class has a body, which is specified inside a pair of braces ({}).

    The body of a class contains its different components, for example, fields, methods, etc.

    The following code defines a class named Dog with an empty body.
    Dog class does not use any modifiers.

    class Dog
    {
    }


    Fields in a Class

    Fields of a class represent properties or attributes for the class.

    Every object of dog class has two properties: a name and a gender.
    The dog class should include declarations of two fields:
        one to represent name and one to represent gender.

    The fields are declared inside the body of the class. The general syntax to declare a field in a class is

        <modifiers> class className
        {
           <modifiers> <data type> <field name> = initialvalue;
           <modifiers> <data type> fieldName;
        }

    A field declaration can use zero or more modifiers.

    The data type of the field precedes its name. Optionally, we can also initialize each field with a value.

    The following code shows how to add fields to a class:

        class Dog
        {
            String name;
            String gender;
        }

    It is a convention in java to start a class name with an uppercase letter and capitalize the subsequent words,
    for example, Table, FirstTime, etc.

    The name of fields and methods should start with a lowercase letter and the subsequent words should be capitalized,
    for example, name, firstName, etc.

    The Dog class declares two fields:
        name and gender. Both fields are of the String type.

    Every instance of the Dog class will have a copy of these two fields.

    Java has two types of fields for a class:

        * Class fields
        * Instance fields

    Sometimes a property belongs to the class itself, not to any particular instance of that class.

    The count of all users should belong to the dog class itself.
    The existence of the count of User is not tied to any specific instance of the User class.

    Only one copy of the class property exists irrespective of the number of instances.

    Class fields are also known as class variables. Instance fields are also known as instance variables.

    The name and gender are two instance variables of the User class.

    All class variables must be declared using the static keyword as a modifier.

    The following code has the declaration of the User class with a count class variable.

    A class variable is known as a static variable.
    An instance variable is known as a non-static variable.
*/

class User {
    String name;           // An instance variable
    String gender;         // An instance variable
    static long count;     // A class variable because of the static modifier
}
