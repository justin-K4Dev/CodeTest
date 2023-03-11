package Object;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Immutable Objects

    An object whose state cannot be changed after it is created is called an immutable object.
    A class whose objects are immutable is called an immutable class.

    An immutable object can be shared by different areas of a program without worrying about its state changes.
    An immutable object is inherently thread-safe.


    Note

    This is how you create an object of the IntWrapper class:

        IntWrapper wrapper  = new IntWrapper(101);

    At this point, the wrapper object holds 101 and there is no way to change it.

    Therefore, the IntWrapper class is an immutable class and its objects are immutable objects.

    It is good practice to declare all instance variables final
    so the Java compiler will enforce the immutability during compile time.
 */

public class ImmutableObjects {

    private final int value;

    public ImmutableObjects( int value ) {
        this.value = value;
    }

    public int GetValue() { return this.value; }

    public static void Test() {

        ImmutableObjects io = new ImmutableObjects( 10 );

        System.out.println( "Original:" + io.GetValue() );
    }
}
