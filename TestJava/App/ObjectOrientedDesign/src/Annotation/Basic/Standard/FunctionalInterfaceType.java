/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Standard;

/*
    FunctionalInterface Annotation Type

    An interface with one abstract method declaration is known as a functional interface.
    A compile-time error is generated if the interfaces annotated with this annotation are not functional interfaces.
 */

@FunctionalInterface
interface FunctionalInterfaceType
{
    void Update();
}

/*
    An interface with only one abstract method is a functional interface no matter whether
    it is annotated with a @FunctionalInterface annotation or not.
 */
