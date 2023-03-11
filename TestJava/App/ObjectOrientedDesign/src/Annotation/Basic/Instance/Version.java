/**
 * Created by justin on 2015-07-14.
 */

package Annotation.Basic.Instance;

/*
    Declaring an Annotation Type

    <modifiers> @interface <annotation-type-name> {
        // Annotation type body
    }

    Annotation Instance

    To create an instance of an annotation type and use it to annotate a program element,
    we use the following syntax:
        @annotationType( name1 = value1,  name2 = value2, names3 = values3... )

    The following code uses an annotation of the Version type,
    with the major element value set to 1 and the minor element value set to 0.
        @Version( major = 1, minor = 0 )

    We can mix the annotation for a program element with its other modifiers.
        @Version ( major = 1, minor = 0 ) public class VersionTest {
        }
        public @Version( major = 1, minor = 0) class VersionTest {
        }
*/

public @interface Version
{
    int major();
    int minor();
}
