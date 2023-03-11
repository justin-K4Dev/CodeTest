/**
 * Created by justin on 2015-07-14.
 */

package Annotation.Basic.Usage;

/*
    Enum Type

    An annotation can have elements of an enum type.
 */

enum Level
{
    PENDING, FAILED, PASSED;
}

@interface Review
{
    Level status() default Level.PENDING;
    String comments() default "";
}


@Review( status = Level.PASSED )
public class EnumType
{

}
