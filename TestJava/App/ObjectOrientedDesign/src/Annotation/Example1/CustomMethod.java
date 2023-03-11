/**
 * Created by justin on 2015-06-02.
 */

package Annotation.Example1;

import java.lang.annotation.*;

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
@Documented
public @interface CustomMethod
{
    public String Name() default "no name";
    public String Description() default "no description";
}