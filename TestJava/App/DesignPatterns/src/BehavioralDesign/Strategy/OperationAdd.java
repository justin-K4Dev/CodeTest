package BehavioralDesign.Strategy;

/**
 * Created by justin on 2015-07-25.
 */

public class OperationAdd implements Strategy{
    @Override
    public int doOperation(int num1, int num2) {
        return num1 + num2;
    }
}