/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Standard;

/*
    Override Annotation Type

    The override annotation type is a marker annotation type which can only be used on methods.

    It indicates that a method overrides a method declared in its supertype.

    If we mean to override a method in a supertype,
    it is recommended to annotate the overridden method with a @Override annotation.

    The compiler will make sure that the annotated method really overrides a method in the supertype.

    If the annotated method does not override a method in the supertype,
    the compiler will generate an error.
 */

class Parent
{
    public void Method() {
    }
}

class Child extends Parent {

    @Override
    public void Method() {
    }
}
