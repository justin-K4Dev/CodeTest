package Object;

/**
 * Created by justin on 2015-08-10.
 */

/*
    Hash Code of an Object

    A hash code is an integer value. The algorithm to compute an integer is called a hash function.

    Java uses hash codes to efficiently retrieve data from hash based collections.

    The Object class has a hashCode() method that returns an int, which is the hash code of the object.

    The default implementation of this method computes the hash code of an object
    by converting the memory address of the object into an integer.

    Here are the rules that we must follow when we override the hashCode() method in your class.

    Suppose there are two object references, x and y.

    If x.equals(y) returns true, x.hashCode() must return an integer, which is equal to y.hashCode().

    If two objects are equal using the equals() method, they must have the same hash codes.

    If x.hashCode() is equal to y.hashCode(), it is not necessary that x.equals(y) returns true.

    If the hashCode() method is called on the same object multiple times,
    the method must return the same integer value.

    If a class overrides any of these two methods,
    it must override both for the objects of the class to work correctly in hash-based collections.

    Java 7 added a utility class java.lang.Objects.
    It contains a hash() method that computes the hash code for any number of values.

    From java 7, use the Objects.hash() method to compute the hash code of an object.
 */

public class HashCode {

    private String title;
    private String author;

    public int GetHashCode() {

        int hash = 37;
        int code = 0;

        // Use title
        code = ( title == null ? 0 : title.hashCode() );
        hash = hash * 59 + code;

        // Use author
        code = ( author == null ? 0 : author.hashCode() );
        hash = hash * 59 + code;

        return hash;
    }
}
