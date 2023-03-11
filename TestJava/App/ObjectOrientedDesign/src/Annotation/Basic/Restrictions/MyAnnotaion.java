/**
 * Created by justin on 2015-07-14.
 */

package Annotation.Basic.Restrictions;

/*
    Restrictions on Annotation Types

    An annotation type cannot inherit from another annotation type.

    Every annotation type implicitly inherits the java.lang.annotation.Annotation interface,
    which is declared as follows:

        package  java.lang.annotation;

        public interface Annotation
        {
            boolean equals( Object obj );
            int  hashCode();
            String toString();
            Class<? extends  Annotation> annotationType();
        }

    Method declarations in an annotation type cannot specify any parameters.

    Method declarations in an annotation type cannot have a throws clause.

    The return type of a method declared in an annotation type must be one of the following types:

        * Any primitive type: byte, short, int, long, float, double, boolean, and char
        * java.lang.String
        * java.lang.Class
        * An enum type
        * An annotation type
        * An array of any of the above mentioned type, for example, String[], int[], etc.

    The return type cannot be a nested array. For example, you cannot have a return type of String[][] or int[][].

    You can declare the annotation method as shown:

        public  @interface MyAnnotation
        {
            Class element1();  // Any Class type
            Class<Test> element2(); // Only  Test   class  type
            Class<? extends Test> element3(); // Test   or  its  subclass type
        }

    An annotation type cannot be generic.
 */

public @interface MyAnnotaion
{
    Class Element1(); // Any Class type
    Class<Test> Element2(); // Only Test class type
    Class<? extends Test>  Element3(); // Test or its subclass type
}
