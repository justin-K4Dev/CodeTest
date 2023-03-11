package BehavioralDesign.Visitor;

/**
 * Created by justin on 2015-07-25.
 */

public interface ComputerPart {
    public void accept(ComputerPartVisitor computerPartVisitor);
}