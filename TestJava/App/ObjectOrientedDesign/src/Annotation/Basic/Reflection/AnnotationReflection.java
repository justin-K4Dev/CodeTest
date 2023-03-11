package Annotation.Basic.Reflection;

/**
 * Created by justin on 2015-08-13.
 */

/*
    Annotation Reflection

    Annotations on a program element are Java objects.

    Program elements that let you access their annotations implement the java.lang.reflect.AnnotatedElement interface.

    The following classes implement the AnnotatedElement interface:

    Methods of the AnnotatedElement interface are used to access annotation on the following listed types of objects.

        java.lang.Class
        java.lang.reflect.Executable
        java.lang.reflect.Constructor
        java.lang.reflect.Field
        java.lang.reflect.Method
        java.lang.reflect.Parameter
        java.lang.Package
        java.lang.reflect.AccessibleObject

    An annotation type must be annotated with the Retention meta-annotation
    with the retention policy of runtime to access it at runtime.
 */