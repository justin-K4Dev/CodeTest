/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Type;

/*
    Target Annotation Type

    Target annotation type annotates an annotation type to set the context to use the annotation type.
    It has only one element named value.
    Its value element is an array of java.lang.annotation.ElementType enum type.
    The following table lists all constants in the ElementType enum.

        Constant Name       Description
        ANNOTATION_TYPE     annotate another annotation type declaration.
                            This makes the annotation type a meta-annotation.
        CONSTRUCTOR         annotate constructors.
        FIELD               annotate fields and enum constants.
        LOCAL_VARIABLE      annotate local variables.
        METHOD              annotate methods.
        PACKAGE             annotate package declarations.
        PARAMETER           annotate parameters.
        TYPE                annotate class, interface (including annotation type), or enum declarations.
        TYPE_PARAMETER      annotate type parameters in generic classes, interfaces, methods, etc.
        TYPE_USE            annotate all uses of types.

    The following Version annotation type has Target meta-annotation,
    which specifies that the Version annotation type can be used with program elements of only three types:
    any type (class, interface, enum, and annotation types), a constructors, and methods.

        import java.lang.annotation.Target;
        import java.lang.annotation.ElementType;

        @Target({ ElementType.TYPE, ElementType.CONSTRUCTOR, ElementType.METHOD })
        @interface Version
        {
            int major();
            int minor();
        }

    The Version annotation cannot be used on any program elements other than
    the three types specified in its Target annotation.
 */

import java.lang.annotation.Target;
import java.lang.annotation.ElementType;

@Target({ ElementType.TYPE_USE })
@interface MyAnnotation1 {
}

@Target({ ElementType.TYPE_USE })
@interface MyAnnotation2 {
}

class TargetType
{
    public void Do() throws @MyAnnotation1 Exception {

        int value = (@MyAnnotation2 int) .02;
        TargetType t = new @MyAnnotation1 TargetType();
    }
}
