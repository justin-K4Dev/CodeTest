/**
 * Created by justin on 2015-06-02.
 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import Example1.Parent;
import Example1.AnnotationLogic;
import Example1.InheritedLogic;

import Example2.Task;


public class Main {

    public static void main( String[] args ) {

        // Example 1 test
        {
            Task task = new Task();
            task.ShowAnnotation();
        }

        // @CustomMethod test
        {
            System.out.println( "Start @CustomMethod test !!!" );

            List<String> customMethodList = new ArrayList<String>();
            Collections.addAll(customMethodList, "justin", "herry", "jully", "max");
            AnnotationLogic.RunCustomMethod(customMethodList, AnnotationLogic.class);

            System.out.println();
        }

        // @CustomType test
        {
            System.out.println( "Start @CustomType test !!!" );

            List<String> customTypeList = new ArrayList<String>();
            Collections.addAll(customTypeList, "fox", "jane");
            AnnotationLogic.RunCustomType(customTypeList, AnnotationLogic.class);

            System.out.println();
        }

        // @Inherited test
        {
            System.out.println( "Start @Inherited test !!!" );

            List<String> customTypeList = new ArrayList<String>();
            Collections.addAll(customTypeList, "fox", "jane");
            AnnotationLogic.RunCustomType(customTypeList, InheritedLogic.class);

            System.out.println();
        }

        // @SuppressWarnings test
        {
            AnnotationLogic al = new AnnotationLogic();
            al.Call();
        }

        // @Deprecated test
        {
            AnnotationLogic al = new AnnotationLogic();
            al.OldDo();
        }

        // @Override test
        {
            AnnotationLogic al = new AnnotationLogic();
            al.Update();

            Parent parent = new Parent();
            parent.Update();
        }
    }
}
