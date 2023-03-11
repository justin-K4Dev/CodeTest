package CreationalDesign.ProtoType;

/**
 * Created by justin on 2015-07-24.
 */
public abstract class Shape implements Cloneable {

    private String id;
    protected String type;

    abstract void Draw();

    public String GetType(){
        return type;
    }

    public String GetID() {
        return id;
    }

    public void SetID(String id) {
        this.id = id;
    }

    @Override
    public Object clone() {

        Object clone = null;

        try {
            clone = super.clone();
        }
        catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }

        return clone;
    }
}
