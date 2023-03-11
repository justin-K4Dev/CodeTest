/**
 * Created by justin on 2015-07-14.
 */

package Annotation.Basic.Usage;

/*
    Primitive Types

    The data type of an element in an annotation type could be any of the primitive data types:
    byte, short, int, long, float, double, boolean, and char.

    The Version annotation type declares two elements, major and minor, and both are of int data type.
    The following code declares an annotation type:
*/

@interface MyData
{
    byte a();

    short b();

    int c();

    long d();

    float e();

    double f();

    boolean g();

    char h();
}

@MyData( a = 1, b = 2, c = 3, d = 4, e = 12.34F, f = 1.89, g = true, h = 'Y' )
public class PrimitiveTypes
{
}

/*
    We can use a compile-time constant expression to specify the value for an element of an annotation.

    The following two instances of the Version annotation are valid:

        @Version( major = 2 + 1, minor = (int)13.2 )
        @Version( major = 3, minor = 13 )
 */