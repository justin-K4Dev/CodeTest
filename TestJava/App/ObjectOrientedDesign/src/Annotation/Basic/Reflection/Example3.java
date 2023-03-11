/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Reflection;

/*
    Example 3

    The following code shows how to get a specific annotation.
 */

import java.lang.annotation.Annotation;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.reflect.AnnotatedElement;
import java.lang.reflect.Method;

@Retention( RetentionPolicy.RUNTIME )
@interface FileVersion {
    int major();
    int minor();
}

@FileVersion( major = 1, minor = 0 )
class AccessAnnotation
{
    @FileVersion( major = 1, minor = 1 )
    public void TestMethod1() {
    }

    @FileVersion( major = 1, minor = 2 )
    @Deprecated
    public void TestMethod2() {
    }
}

public class Example3
{
    public static void Test() {

        Class<AccessAnnotation> c = AccessAnnotation.class;
        System.out.println( "Annotations for class: " + c.getName() );
        PrintAnnotations( c );

        System.out.println( "Method annotations: " );
        Method[] m = c.getDeclaredMethods();
        for ( int i = 0; i < m.length; i++ ) {

            System.out.println( "Annotations for method: " + m[i].getName() );
            PrintAnnotations( m[i] );
        }
    }
    // The code above generates the following result.
        // Annotations for method: AccessAnnotation
        // @Version(major=1, minor=0)
        // Found Version annoation: major=1, minor=0
        // Method annotation:
        // Annotations for method: TestMethod2
        // @Version(major=1, minor=2)
        // Found Version annoation: major=1, minor=2
        // @java.lang.Deprecated()
        // Annotations for method: TestMethod1
        // @Version(major=1, minor=1)

    public static void PrintAnnotations( AnnotatedElement programElement ) {

        Annotation[] annList = programElement.getAnnotations();
        for ( int i = 0; i < annList.length; i++ ) {

            System.out.println( annList[i] );

            if ( annList[i] instanceof Version ) {
                Version v = (Version) annList[i];
                int major = v.major();
                int minor = v.minor();
                System.out.println( "Found Version annotation: " + "major = " + major + ", minor = " + minor );
            }
        }
    }
}
