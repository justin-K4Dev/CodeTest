package Annotation.Example2;

/**
 * Created by justin on 2015-06-08.
 */
import java.lang.annotation.Annotation;
import java.lang.reflect.Method;

public class Task {

    public static void ShowAnnotation() {
        try {
            Method m = Task.class.getMethod( "Do" ); // get annotation by Method

            System.out.println( "call getAnnotationsByType() !!!" );
            {
                Annotation[] annotationList = m.getAnnotationsByType(Schedule.class);
                for (Annotation an : annotationList) {
                    System.out.println("Annotation : " + an);
                }
            }

            System.out.println( "call getAnnotation() !!!" );
            {
                ScheduleList sl = m.getAnnotation( ScheduleList.class );

                for ( Schedule s : sl.value() ) {
                    System.out.println( "Annotation : " + s );
                }
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Schedule( dayOfMonth="Last" )
    @Schedule( dayOfWeek="Fri", hour="23" )
    public void Do() {

    }
}
