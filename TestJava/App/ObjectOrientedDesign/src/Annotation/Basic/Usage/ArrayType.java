/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Usage;

/*
    Array Type Annotation Element

    An annotation can have elements of an array type.
    The array type could be of one of the following types:

        A primitive type
        java.lang.String type
        java.lang.Class type
        An enum type
        An annotation type

    We need to specify the value for an array element inside braces.
    Elements of the array are separated by a comma.
 */

@interface ItemList
{
    String[] items();
}

@ItemList( items = { "A", "B" } )
public class ArrayType
{
}

/*
    If you have only one element in the array, it is allowed to omit the braces.

        @ToDo( items = {"A"} )
        @ToDo( items = "A" )

    To pass in an empty array

        @ToDo( items = {} )
 */