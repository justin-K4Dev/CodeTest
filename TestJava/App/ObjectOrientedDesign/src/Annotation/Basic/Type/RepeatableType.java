/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Type;

/*
    Repeatable Annotation

    Java 8 added a Repeatable meta-annotation type.

    An annotation type declaration must be annotated with a @Repeatable annotation
    if we would use it repeatly on one single code element.

    The Repeatable annotation type has only one element named value
    whose type is a class type of another annotation type.
 */

import java.lang.annotation.Repeatable;

@interface LogHistory {
    Log[] value();
}

@Repeatable( LogHistory.class )
@interface Log
{
    String date();
    String comments();
}

@Log( date = "01/01/2014", comments = "A" )
@Log( date = "01/21/2014", comments = "B" )
class RepeatableType
{
}
