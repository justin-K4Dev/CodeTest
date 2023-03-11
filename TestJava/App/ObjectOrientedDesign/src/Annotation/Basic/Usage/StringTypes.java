/**
 * Created by justin on 2015-07-14.
 */

package Annotation.Basic.Usage;

/*
    String Types

    We can use an element of the String type in an annotation type.

    The following code defines an annotation type called Name.
    It has two elements, first and last, which are of the String type.

    It is valid to use the string concatenation operator + in the value expression for an element of a String type.

        @Name( first = "Ja" + "ck", last = "Ia" + "an" )
*/

@interface Name
{
    String first();
    String last();
}

@Name( first = "Tom", last = "Smith" )
public class StringTypes
{
    @Name( first = "Jack", last = "Iaan" )
    public void Method() {
    }
}
