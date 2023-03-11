/**
 * Created by justin on 2015-06-03.
 */

package Annotation.Example1;

import java.lang.reflect.Method;
import java.util.List;

@CustomType( Name = "fox" )
public class AnnotationLogic extends Parent {

    @Override
    public void Update () {
        System.out.println( "Call AnnotationLogic::Update() !!!" );
    }

    /**
     * AnnotationLogic �� Do
     * @Deprecated - use new method NewDo() !!!
     */
    @Deprecated
    public void OldDo() {
        // deprecated method
    }

    public void NewDo() {
    }

    @SuppressWarnings( { "unchecked", "deprecation" } )
    public void Call() {
        OldDo();
    }

    @CustomMethod( Name = "justin", Description = "Hi justin !!!" )
    public boolean ValidateValue( String value ) {
        return ( value.matches( "\\w*\\d\\w*" ) );
    }

    @CustomMethod( Name = "jully" )
    public String EncryptValue( String value ) {
        return new StringBuilder( value ).reverse().toString();
    }

    @CustomMethod( Name = "herry", Description = "Hi herry ^^" )
    public boolean CheckForNewValue( List<String> prevValue, String newValue ) {
        return ! prevValue.contains( newValue );
    }

    public static void RunCustomMethod( List<String> customAnnotationList, Class<?> clazz ) {
        for( Method m : clazz.getDeclaredMethods() ) {
            CustomMethod cst = m.getAnnotation( CustomMethod.class );
            if( null != cst ){
                System.out.println( "Found CustomMethod Annotation : " + cst.Name() + " " + cst.Description() );
                customAnnotationList.remove( new String( cst.Name() ) );
            }
        }
        for( String str : customAnnotationList ) {
            System.out.println( "Warning : Missing CustomMethod annotation Name : " + str );
        }
    }

    public static void RunCustomType( List<String> customAnnotationList, Class<?> clazz ) {

        CustomType[] cstList = clazz.getAnnotationsByType( CustomType.class );
        for ( CustomType cst : cstList ) {
            System.out.println( "Found CustomType Annotation : " + cst.Name() + " " + cst.Description() );
            customAnnotationList.remove( new String( cst.Name() ) );
        }

        for( String str : customAnnotationList ) {
            System.out.println( "Warning : Missing CustomType annotation Name : " + str );
        }
    }
}
