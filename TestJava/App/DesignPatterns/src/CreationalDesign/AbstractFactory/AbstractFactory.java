package CreationalDesign.AbstractFactory;

/**
 * Created by justin on 2015-07-19.
 */

public abstract class AbstractFactory {

    abstract Color GetColor(String color);
    abstract Shape GetShape(String shape) ;
}
