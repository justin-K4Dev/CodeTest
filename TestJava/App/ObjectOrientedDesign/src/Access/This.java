package Access;

/**
 * Created by justin on 2015-08-10.
 */

/*
    What Is this ?

    Java has a keyword called this.
    It is a reference to the current instance of a class.

    It can be used only in the context of an instance.

    The following code shows how to use this keyword.

        public class Main {
            int varA = 1;
            int varB = varA; // Assign value of varA to varB
            int varC = this.varA; // Assign value of varA to varC
        }

    We need to qualify an instance variable with the keyword this
    and a class variable with the class name when the instance variable
    or the class variable is hidden by another variable with the same name.


    Note

    Sometimes it is easier to keep the variable names the same, as they represent the same thing.

    For example, the following code is very common:

    The Student class declares an instance variable id. In its setId() method,
    it also names the parameter id, and uses this.id to refer to the instance variable.

    It also uses this.id to refer to the instance variable id in its getId() method.
 */

class Student
{
    private int id; // An instance variable

    public void SetID( int id ) {
        this.id = id;
    }

    public int GetID() {
        return this.id;
    }
}

public class This {

    /*
        The following code shows how to use the this Keyword to Refer to an Instance Variable
        Whose Name Is Hidden by a Local Variable.
    */
    int num = 2014; // An instance variable
    void printNum( int num ) {
        System.out.println( "Parameter num: " + num );
        System.out.println( "Instance variable num: " + this.num );
    }

    public static void Test1() {
        This tt6 = new This();
        tt6.printNum( 2000 );
    }

    /*
        We can use the keyword this to qualify an instance method name.
        The following code shows the Method1() method invoking the Method2() method using the keyword this.
    */
    void Method1() {
        // Invoke the Method2() method
        this.Method2(); // same as "Method2();"
    }

    void Method2() {
        // do something
    }
}
