/**
 * Created by justin on 2015-07-14.
 */

package Annotation.Basic.Instance;

@Version( major = 1, minor =  0 )
public class Logic
{
    @Version( major = 1, minor = 1 )
    private int value = 110;

    @Version( major = 1, minor = 0 )
    public Logic() {
    }

    @Version( major = 1, minor = 1 )
    public Logic( int value ) {
        this.value = value;
    }

    @Version( major = 1, minor = 0 )
    public void PrintData() {
    }

    @Version( major = 1, minor = 1 )
    public void SetValue( int value ) {

        @Version( major = 1, minor = 2 )
        int newValue = value;

        this.value = value;
    }
}
