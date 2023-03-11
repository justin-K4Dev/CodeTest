package BehavioralDesign.Command;

/**
 * Created by justin on 2015-07-24.
 */

public class BuyStock implements Order {

    private Stock abcStock;

    public BuyStock(Stock abcStock){
        this.abcStock = abcStock;
    }

    public void execute() {
        abcStock.buy();
    }
}