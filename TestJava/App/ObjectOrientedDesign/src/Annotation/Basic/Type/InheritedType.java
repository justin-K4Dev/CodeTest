/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Type;

/*
    Inherited Annotation Type

    Inherited annotation type is a marker meta-annotation type.

    If an annotation type is annotated with an Inherited meta-annotation,
    its instances are inherited by a subclass declaration.

    It has no effect if an annotation type is used to annotate any elements other than a class declaration.

    The following code shows the effect of @Inherited meta-annotation type.
 */

import java.lang.annotation.Inherited;

@interface MyAnnotation11 {
    int id();
}

@Inherited
@interface MyAnnotation12 {
    int id();
}

@MyAnnotation11( id = 1 )
@MyAnnotation12( id = 2 )
class Parent
{
}

// Class Child inherits MyAnnotation12( id = 2 ) annotation from the class Parent
class Child extends Parent
{
}
