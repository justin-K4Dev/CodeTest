/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Reflection;

/*
    Example 4

    The following code shows how to access Instances of Repeatable Annotations at Runtime
 */

import java.lang.annotation.Repeatable;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
@interface LogHistory {
    Log[] value();
}
@Repeatable( LogHistory.class )
@interface Log
{
    String date();
    String comments();
}

@Log( date = "02/01/2014", comments = "A" )
@Log( date = "01/22/2014", comments = "B" )
public class Example4 {

    public static void Test() {

        Class<Example4> mainClass = Example4.class;

        Log[] annList = mainClass.getAnnotationsByType( Log.class );
        for ( Log log : annList ) {
            System.out.println( "Date = " + log.date() + ", Comments = " + log.comments() );
        }

        Class<LogHistory> containingAnnClass = LogHistory.class;
        LogHistory logs = mainClass.getAnnotation( containingAnnClass );
        for ( Log log : logs.value() ) {
            System.out.println( "Date = " + log.date() + ", Comments = " + log.comments() );
        }
    }
    // The code above generates the following result.
        // Date=02/01/2014, Comments=A
        // Date=01/22/2014, Comments=B
        // Date=02/01/2014, Comments=A
        // Date=01/22/2014, Comments=B
}

