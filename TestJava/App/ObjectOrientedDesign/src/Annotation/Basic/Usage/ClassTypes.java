/**
 * Created by justin on 2015-07-14.
 */

package Annotation.Basic.Usage;

import java.io.IOException;

/*
    Class Types

    The following code shows how to use Class type as the annotation value.
 */

@interface MyThrow
{
    Class<? extends Throwable> WillThrow() default java.lang.Throwable.class;
}

public class ClassTypes
{
    @MyThrow( WillThrow = IOException.class )
    public static void TestCase1() {
        // code goes here
    }

    @MyThrow()
    public static void TestCase2() {
        // code goes here
    }
}
