package Annotation.Example2;

/**
 * Created by justin on 2015-06-08.
 */
import java.lang.annotation.Target;
import static java.lang.annotation.ElementType.*;
import java.lang.annotation.Retention;
import static java.lang.annotation.RetentionPolicy.*;

@Target( METHOD )
@Retention( RUNTIME )
public @interface ScheduleList
{
    Schedule[] value();
}