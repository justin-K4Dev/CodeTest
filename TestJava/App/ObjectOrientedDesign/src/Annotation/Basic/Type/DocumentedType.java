/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Type;

/*
    Documented Annotation

    Documented annotation type is a marker meta-annotation type.

    If an annotation type is annotated with a Documented annotation,
    the Javadoc tool will generate documentation for all of its instances.
 */

import java.lang.annotation.Documented;

@Documented
@interface ProgramVersion
{
    int major();
    int minor();
}

@ProgramVersion( major = 1, minor = 0 )
public class DocumentedType
{
}
