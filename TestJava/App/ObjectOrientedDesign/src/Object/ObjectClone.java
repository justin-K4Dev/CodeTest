package Object;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Object Clone

    Java does not provide an automatic mechanism to clone (copy) an object.
    Cloning an object means copying the content of the object bit by bit.

    To support clone operation, implement the clone() method in the class.
    The declaration of the clone() method in the Object class is as follows:

        protected Object clone() throws CloneNotSupportedException

    clone() method is declared protected. Therefore, we cannot call it from the client code.
    The following code is not valid:

        Object obj  = new Object();
        Object clone = obj.clone(); // Error. Cannot access protected clone() method

    We need to declare the clone() method public in a class to clone objects of the class.

    Its return type is Object. It means you will need to cast the returned value of the clone() method.

    Suppose MyClass is cloneable. The cloning code will look as

        MyObject mc  = new MyObject();
        MyObject clone = (MyObject)mc.clone(); // Need to use  a  cast

    The clone() method in the Object class throws a CloneNotSupportedException.
    To call the clone() method, we need to place the call in a try-catch block, or rethrow the exception.
 */

class MyObject implements Cloneable
{
    private double value;

    public MyObject( double value ) {
        this.value = value;
    }

    public void setValue( double value ) {
        this.value = value;
    }

    public double getValue() {
        return this.value;
    }

    public Object clone() {

        MyObject copy = null;
        try {
            copy = (MyObject) super.clone();
        } catch ( CloneNotSupportedException e ) {
            e.printStackTrace();
        }
        return copy;
    }
}

class ShallowClone implements Cloneable
{
    private MyObject holder = new MyObject( 0.0 );

    public ShallowClone( double value ) {
        this.holder.setValue( value );
    }

    public void setValue( double value ) {
        this.holder.setValue( value );
    }

    public double getValue() {
        return this.holder.getValue();
    }

    public Object clone() {
        ShallowClone copy = null;
        try {
            copy = (ShallowClone) super.clone();
        } catch ( CloneNotSupportedException e ) {
            e.printStackTrace();
        }
        return copy;
    }
}

class DeepClone implements Cloneable {
    private MyObject holder = new MyObject( 0.0 );

    public DeepClone( double value ) {
        this.holder.setValue( value );
    }

    public void setValue( double value ) {
        this.holder.setValue( value );
    }

    public double getValue() {
        return this.holder.getValue();
    }
    public Object clone() {
        DeepClone copy = null;
        try {
            copy = (DeepClone) super.clone();
            copy.holder = (MyObject) this.holder.clone();
        } catch ( CloneNotSupportedException e ) {
            e.printStackTrace();
        }
        return copy;
    }
}

public class ObjectClone
{
    /*
        The following code shows how to implement a clone method.
     */
    public static void TestClone() {
        MyObject dh = new MyObject( 100.00 );

        MyObject dhClone = (MyObject) dh.clone();

        System.out.println("Original:" + dh.getValue());
        System.out.println("Clone :" + dhClone.getValue());

        dh.setValue( 200.00 );
        dhClone.setValue( 400.00 );

        System.out.println("Original:" + dh.getValue());
        System.out.println("Clone :" + dhClone.getValue());
    }
    // The code above generates the following result.
        // Sat Jun 27 18:34:32 PDT 2015
        // Sat Jun 27 18:34:32 PDT 2015

    /*
        The following code is not returning Object type from clone method, which is compiled only in Java 5 or later.
     */
    public static void TestShallowClone() {

        ShallowClone sc = new ShallowClone( 100.00 );
        ShallowClone scClone = (ShallowClone) sc.clone();

        System.out.println("Original:" + sc.getValue());
        System.out.println("Clone :" + scClone.getValue());

        sc.setValue( 200.00 );

        System.out.println("Original:" + sc.getValue());
        System.out.println("Clone :" + scClone.getValue());
    }
    // The code above generates the following result.
        // Original:100.0
        // Clone:100.0
        // Original:200.0
        // Clone:200.0

    /*
        The code in the clone() method of the ShallowClone class is the same as for
        the clone() method of the MyClass class.

        When the ShallowClone class calls the clone() method of the Object class using super.clone(),
        it receives a shallow copy of itself.
        That is, it shares the DoubleHolder object used in its instance variable with its clone.

        In a deep cloning, you need to clone all objects referenced by all reference instance variables of an object.
     */
    public static void TestDeepClone() {

        DeepClone sc = new DeepClone( 100.00 );
        DeepClone scClone = (DeepClone) sc.clone();

        System.out.println("Original:" + sc.getValue());
        System.out.println("Clone :" + scClone.getValue());

        sc.setValue( 200.00 );

        System.out.println("Original:" + sc.getValue());
        System.out.println("Clone :" + scClone.getValue());
    }
    // The code above generates the following result.
        // Original:100.0
        // Clone:100.0
        // Original:200.0
        // Clone:100.0
}
