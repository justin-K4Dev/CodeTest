package Interface;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Interface

    What Is an Interface?

    An interface in Java defines a reference type to create an abstract concept.
    The interface is implemented by classes to provide an implementation of the concept.

    Prior to Java 8, an interface could contain only abstract methods.
    Java 8 allows an interface to have static and default methods with implementation.

    Interfaces define a relationship between unrelated classes through the abstract concept.

    For example, we can create a Person class to represent a person and we can create a Dog class to represent a dog.

    Both person and dog can walk.
    The walk here is a abstract concept.
    The dog can walk and so does the person.
    Here we can create an interface called Walkable to represent the walk concept.
    Then we can have the Person class
    and Dog class to implement the Walkable concept and provide their own implementation.
    The Person class implements the Walkable interface and makes the person to walk in a human being way.
    And the Dog class can implement the Walkable interface and makes the dog to walk in a dog way.


    Example

    In the following we will use an example to show why do we need interface.
    Suppose Person class has a walk() method.

        public interface Walkable
        {
            void walk();
        }

        class Person implements Walkable
        {
            public Person() {
            }

            public void walk() {
                System.out.println( "a person is walking." );
            }
        }

        class Dog implements Walkable
        {
            public Dog() {
            }
            public void walk() {
                System.out.println( "a dog is walking." );
            }
        }

    A class can implement one or more interfaces using the keyword implements in its declaration.

    By implementing an interface,
    a class guarantees that it will provide an implementation for all methods declared in the interface
    or the class will declare itself abstract.

    If a class implements the Walkable interface, it must provide implementation for the walk() method.
    Like a class, an interface defines a new reference type.

    When defining a new interface (e.g. Walkable), we define a new reference interface type.
    The following declaration is valid:

        Walkable w;  // w is a reference variable of type Walkable

    You cannot create an object of an interface type since the interface is to define an abstract concept.
    The following code is invalid:

        new Walkable(); // A compile-time error

    We can create an object only for a class type,
    but we can use an interface type variable can refer to any object whose class implements that interface.

    Because the Person and Dog classes implement the Walkable interface,
    a reference variable of the Walkable type can refer to an object of these classes.

        Walkable w1 = new Person(); // OK
        Walkable w2 = new Dog();    // OK

    We can access any members of the interface using its reference type variable.
    Since Walkable interface has only one member, which is the walk() method, we can write code as shown:

        // Let  the   person  walk
        w1.walk();
        // Let  the   dog walk
        w2.walk();

    When invoking the walk() method on w1, it invokes the walk() method of the Person object
    because w1 is referring to a Person object.

    When invoking the walk() method on w2, it invokes the walk() method of the Dog object
    because w2 is referring to a Dog object.

    When calling a method using a reference variable of an interface type,
    it calls the method on the object to which it is referring.


    Example 2

    The following code created a method to use interface we parameter type.

        public class Main
        {
            public static void main( String[] args ) {

                Walkable[] w = new Walkable[2];
                w[0] = new Person();
                w[1] = new Dog();

                Walkables.letThemWalk( w );
            }
        }

        class Walkables
        {
            public static void letThemWalk( Walkable[] list ) {
                for ( Walkable w : list ) {
                    w.walk();
                }
            }
        }


    Declaring an Interface

    The general syntax for declaring an interface is

        <modifiers> interface <interface-name>
        {
            Constant-Declaration
            Method-Declaration
            Nested-Type-Declaration
        }

    An interface declaration starts with list of modifiers, which may be empty.
    Like a class, an interface can have a public or package-level scope.

    The keyword public is used to indicate that the interface has a public scope.
    Absence of a scope-modifier indicates that the interface has a package-level scope.

    An interface with a package-level scope can be referred to only within the members of its package.
    The keyword interface is used to declare an interface and is followed by the name of the interface.

    The name of an interface must be a valid Java identifier.
    An interface body follows its name and is placed inside braces.

    The body of an interface can be empty. The following is the simplest interface declaration:

        package com.java2s;

        interface Updatable
        {
            // The interface body  is empty
        }

    Like a class, an interface has a simple name and a fully qualified name.
    The identifier that follows the keyword interface is its simple name.

    The fully qualified name of an interface is formed by using its package name and the simple name separated by a dot.

    In the above example, Updatable is the simple name and com.java2s.Updatable is the fully qualified name.
    The rules of using simple and fully qualified name of an interface are the same as that of a class.

    The following code declares an interface named ReadOnly. It has a public scope.

        package  com.java2s;

        public interface ReadOnly
        {
            // The interface body is empty
        }

    An interface declaration is always abstract whether you declare it abstract explicitly or not.


    Marker Interfaces

    Marker Interfaces are interfaces with no members.
    A marker interface marks the class with a special meaning.

        interface Shape {
        }

        class Circle implements Shape {
        }

        Shape c = new Circle();

        if ( c instanceof Shape )  {
           System.out.println( "Using a Shape object" );
        }

    Java API has many marker interfaces.
    The java.lang.Cloneable, java.io.Serializable, and java.rmi.Remote are all the marker interfaces.


    Functional Interfaces

    An interface with just one abstract method is known as a functional interface.


    Polymorphism-One Object, Many Views

    Polymorphism refers to the ability of an object to take on many forms.
    polymorphism is an ability of an object to provide its different views.

    Interfaces let us create a polymorphic object.
*/


public class Interface {
}
