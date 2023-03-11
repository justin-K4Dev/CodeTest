package StructuralDesign.Bridge;

/**
 * Created by justin on 2015-07-24.
 */

public abstract class Shape {

    protected DrawAPI drawAPI;

    protected Shape( DrawAPI drawAPI ) {
        this.drawAPI = drawAPI;
    }

    public abstract void draw();
}