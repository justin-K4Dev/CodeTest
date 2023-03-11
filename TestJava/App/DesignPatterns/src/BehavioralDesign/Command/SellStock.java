package BehavioralDesign.Command;

/**
 * Created by justin on 2015-07-24.
 */

public class SellStock implements Order {
    private Stock abcStock;

    public SellStock(Stock abcStock){
        this.abcStock = abcStock;
    }

    public void execute() {
        abcStock.sell();
    }
}