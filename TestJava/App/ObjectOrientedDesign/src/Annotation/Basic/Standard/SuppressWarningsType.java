/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Standard;

/*
    SuppressWarnings Annotation Type

    The SuppressWarnings is used to suppress named compiler warnings.
    It declares one element named value whose data type is an array of String.
 */

import java.util.ArrayList;

public class SuppressWarningsType
{
    @SuppressWarnings( "unchecked" )
    public void Test() {
        @SuppressWarnings( "rawtypes" )
        ArrayList list = new ArrayList();
        list.add( "Hello" ); // The compiler issues an unchecked warning
    }
}
