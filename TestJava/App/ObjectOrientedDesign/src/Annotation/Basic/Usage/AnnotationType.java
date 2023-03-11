/**
 * Created by justin on 2015-07-14.
 */

package Annotation.Basic.Usage;

/*
    Annotation Type

    We can use an annotation type as the type of an element inside another annotation type's declaration.
    To provide a value for an element of an annotation type,
    use the syntax that is used to create an annotation type instance.
 */

@interface Nickname
{
    String first();
    String last();
}

@interface Version
{
    int major();
    int minor() default 0;
}

@interface Description
{
    Nickname name();
    Version version();
    String comments() default "";
}

@Description( name = @Nickname( first = "Tom", last = "Smith" ), version = @Version( major = 1, minor = 2 ), comments = "Just a  test class" )
public class AnnotationType
{

}
