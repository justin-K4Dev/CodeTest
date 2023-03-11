package Class;

/**
 * Created by justin on 2015-08-03.
 */

/*
    Access Level

    Class simple name is the name between class keyword and {.

    When we refer to a class by its simple name,
    the compiler looks for that class declaration in the same package where the referring class is.

    We can use full name to reference a class as follows.

        com.java2s.Dog aDog;

    The general syntax specifying access-level for a class is

        <access level modifier>class <class name> {
            // Body of the class
        }

    There are only two valid values for <access level modifier> in a class declaration:

        * no value
        * public

    No value is known as package-level access.
    A class with package-level access can be accessed only within the package in which it has been declared.

    Class with public access level modifier can be accessed from any package in the application.

        package com.java2s;

        public class Dog  {

        }
 */