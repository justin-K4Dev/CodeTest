/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Usage;

/*
    Shorthand Annotation Syntax

    Suppose we have an annotation type as follows.

        public @interface Enabled  {
            boolean status() default true;
        }

    To annotate a program element with the Enabled annotation type with the default value,
    we can use the @Enabled() syntax.
    We do not need to specify the values for the status element
    because it has a default value.
    We can further omit the parentheses.

        @Enabled
        public class Logic {
        }

        @Enabled()
            public class Logic {
        }
 */

/*
    An annotation type with only one element has a shorthand syntax.

    If an annotation type has only one element with named value,
    we can omit the name from name = value pair.

    The following code declares a Company annotation type,
    which has only one element named value:
 */

@interface Company
{
    String value();
}

@interface CompanyList
{
    String[] value();
}

/*
    We can omit the name from name = value pair when using the Company annotation.
        @Company( value = "Inc." )
    becomes
 */
@Company( "Inc." )

/*
    The following code shows how to use this shorthand if the element data type is an array.
        @CompanyList( { "A", "B" } )
    We can further omit the braces if we specify only one element in the array annotation type.
 */
@CompanyList( "A" )

public class ShorthandSyntax
{
}
