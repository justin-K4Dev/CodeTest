/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Reflection;

/*
    Example 1

    Suppose you have a Test class and you want to print all its annotations.
    The following snippet of code will print all annotations on the class declaration of the Test class:
 */

import java.lang.annotation.Annotation;

@SuppressWarnings( "unchecked" )
@Deprecated
public class Example1 {

    public static void Test() {

        // Get the class object reference
        Class<Example1> c = Example1.class;

        // Get all annotations on the class declaration
        Annotation[] allAnns = c.getAnnotations();
        System.out.println( "Annotation count: " + allAnns.length );

        // Print all annotations
        for ( Annotation ann : allAnns ) {
            System.out.println( ann );
        }
    }
    // The code above generates the following result.
        // Annotation count: 1
        // @java.lang.Depreacated()
}
