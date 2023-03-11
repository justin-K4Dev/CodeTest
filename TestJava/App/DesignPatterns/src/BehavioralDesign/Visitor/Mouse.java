package BehavioralDesign.Visitor;

/**
 * Created by justin on 2015-07-25.
 */

public class Mouse implements ComputerPart {

    @Override
    public void accept(ComputerPartVisitor computerPartVisitor) {
        computerPartVisitor.visit(this);
    }
}