package Exception;

/**
 * Created by justin on 2015-08-11.
 */

/*
    try-with-resources Block

    Java 7 added a new construct called try-with-resources.

    With the new try-with-resources construct in Java 7, the above code can be written as

        try ( AnyResource aRes = create the resource... ) {
            // Work with the resource here.
            // The resource will be  closed automatically.
        }

    The try-with-resources construct automatically closes the resources when the program exits the construct.

    A try-with-resource construct may have one or more catch blocks and/or a finally block.

    We can specify multiple resources in a try-with-resources block. Two resources must be separated by a semicolon.

    The last resource must not be followed by a semicolon.

    The following code shows some usage of try-with-resources to use one and multiple resources:

        try ( AnyResource  aRes = getResource1() )  {
            // Use aRes here
        }

        try ( AnyResource  aRes1 = getResource1(); AnyResource aRes2 = getResource2() )  {
            // Use aRes1 and aRes2 here
        }

    The resources that we specify in a try-with-resources are implicitly final.

    A resource that in a try-with-resources must be of the type java.lang.AutoCloseable.

    Java 7 added the AutoCloseable interface, which has a close() method.

    When the program exits the try-with-resources block,
    the close() method of all the resources is called automatically.

    In the case of multiple resources,
    the close() method is called in the reverse order in which the resources are specified.
 */

class MyResource implements AutoCloseable
{
    public MyResource() {
        System.out.println( "Creating MyResource." );
    }

    @Override
    public void close() {
        System.out.println( "Closing MyResource..." );
    }
}

public class TryWithResourcesBlock
{
    public static void Test() {
        try ( MyResource mr1 = new MyResource();
              MyResource mr2 = new MyResource() ) {
        }
    }
    // The code above generates the following result.
        // Creating MyResource.
        // Creating MyResource.
        // Closing MyResource...
        // Closing MyResource...
}
