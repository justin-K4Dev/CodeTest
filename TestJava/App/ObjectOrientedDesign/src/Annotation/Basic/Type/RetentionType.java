/**
 * Created by justin on 2015-07-15.
 */

package Annotation.Basic.Type;

/*
    The Retention Annotation

    Retention Annotation sets the retention policy of an annotation type.

    An annotation can be retained at three levels.
        * Source code only
        * Class file only. The default behaviour.
        * Class file and the runtime

    The Retention meta-annotation type specifies how an annotation should be retained by Java.

    If an annotation type has a "source code only" retention policy,
    its instances are removed when compiled into a class file.

    If the retention policy is "class file only", its instances are retained in the class file,
    but they cannot be read at runtime.

    If the retention policy is "class file and runtime", the annotation instances are retained in the class file
    and they are available for reading at runtime.

    The Retention meta-annotation type declares one element, named value, which is of the java.lang.
    annotation.RetentionPolicy enum type.

    The RetentionPolicy enum has three constants, SOURCE, CLASS, and RUNTIME,
    which are used to specify the retention policy of source only, class only, and class-and-runtime, respectively.

    The following code uses the Retention meta-annotation on the Version annotation type.
    It specifies that the Version annotations should be available at runtime.

    If we do not use the Retention meta-annotation on an annotation type,
    its retention policy defaults to class file only.
    And we will not be able to read those annotations at runtime.

    An annotation on a local variable declaration is never available in the class file
    or at runtime irrespective of the retention policy of the annotation type.
 */

import java.lang.annotation.Target;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Target({ ElementType.TYPE, ElementType.CONSTRUCTOR, ElementType.METHOD })
@Retention(RetentionPolicy.RUNTIME)
@interface FileVersion
{
    int major();
    int minor();
}

class RetentionType
{
}