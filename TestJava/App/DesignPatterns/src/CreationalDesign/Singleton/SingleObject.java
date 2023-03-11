package CreationalDesign.Singleton;

/**
 * Created by justin on 2015-07-23.
 */

public class SingleObject {

    //create an object of SingleObject
    private static SingleObject instance = new SingleObject();

    //make the constructor private so that this class cannot be
    //instantiated by other class
    private SingleObject() { }

    //Get the only object available
    public static SingleObject GetInstance(){
        return instance;
    }

    public void ShowMessage(){
        System.out.println( "Hello World !!!" );
    }
}
