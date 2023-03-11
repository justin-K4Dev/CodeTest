/**
 * Created by justin on 2015-06-02.
 */

package Annotation.Example1;

import java.lang.annotation.*;

@Inherited
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.TYPE)
@Documented
public @interface CustomType
{
    public String Name() default "no name";
    public String Description() default "no description";
}