/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Reflection;

/*
    Example 2

    The following code shows how to get a specific annotation.
 */

import java.lang.annotation.Documented;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention( RetentionPolicy.RUNTIME )
@Documented
@interface Version
{
    int major();
    int minor();
}

@Version( major = 1, minor = 2 )
public class Example2
{
    public static void Test() {

        Class<Example2> c = Example2.class;

        Version v = c.getAnnotation( Version.class );
        if ( v == null ) {
            System.out.println( "Version annotation is not present." );
        }
        else {
            int major = v.major();
            int minor = v.minor();

            System.out.println( "Version: major = " + major + ", minor = " + minor );
        }
    }
    // The code above generates the following result.
        // Version: major = 1, minor = 2
}
