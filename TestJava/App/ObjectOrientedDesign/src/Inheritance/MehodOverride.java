package Inheritance;

/**
 * Created by justin on 2015-08-11.
 */

/*
    Method Override

    Redefining an instance method in a class inherited from the superclass, is called method overriding.


    Example

    Let's consider the following declarations of class A and class B:

        public class A
        {
            public void  print() {
                System.out.println( "A" );
            }
        }

        public class B extends A
        {
            public void print() {
                System.out.println( "B" );
            }
        }

    Class B is a subclass of class A.
    Class B inherits the print() method from its superclass and redefines it.

    The print() method in class B overrides the print() method of class A.

    If a class overrides a method, it affects the overriding class and its subclasses.
    Consider the following declaration of class C:

        public class C extends B
        {
            // Inherits B.print()
        }

    Class C does not declare any methods.
    It inherits the print() method from class B.


    Note

    The class always inherits what is available from its immediate superclass.
    The method must be an instance method. Overriding does not apply to static methods.

    The overriding method must have the same name as the overridden method.
    The overriding method must have the same number of parameters of the same type
    in the same order as the overridden method.

    When the method's parameters use generic type, consider the erasure of the generic type parameter,
    not the generic type itself when comparing with other methods.

    The name of the parameter does not matter.

    If the return type of the overridden method is a reference type,
    the return type of the overriding method must be assignment compatible to the return type of the overridden method.


    Access Level

    The access level of the overriding method must be at least the same
    or more relaxed than that of the overridden method.

    The following table lists allowed Access Levels for an Overriding Method

        Overridden Method Access Level      Allowed Overriding Method Access Level
        public                              public
        protected                           public, protected
        package-level                       public, protected, package-level

    A method may include a list of checked exceptions in its throws clause.
    The overriding method cannot add a new exception to the list of exceptions in the overridden method.

    It may remove one or all exceptions or it may replace an exception with another exception.


    Accessing Overridden Method

    To access the overridden method from a subclass.
    A subclass can use the keyword super as a qualifier to call the overridden method of the superclass.

        class MySuperClass
        {
            public void print() {
                System.out.println( "Inside MySuperClass" );
            }
        }

        class MySubClass extends MySuperClass
        {
            public void print() {

                // Call print() method of MySuperClass class
                super.print();
                // Print a message
                System.out.println( "Inside MySubClass.print()" );
            }

            public void callOverridenPrint() {

                // Call print() method of MySuperClass class
                super.print();
            }
        }

        public class Main
        {
            public static void main(String[] args) {

                MySubClass aoSub = new MySubClass();
                aoSub.print();
                aoSub.callOverridenPrint();
            }
        }

    The code above generates the following result.
        Inside MySuperClass
        Inside MySubClass.print()
        Inside MySuperClass
 */

public class MehodOverride
{
}
