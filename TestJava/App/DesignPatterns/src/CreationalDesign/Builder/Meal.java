package CreationalDesign.Builder;

/**
 * Created by justin on 2015-07-24.
 */

import java.util.ArrayList;
import java.util.List;

public class Meal {

    private List<Item> items = new ArrayList<Item>();

    public void AddItem(Item item){
        items.add(item);
    }

    public float GetCost(){
        float cost = 0.0f;

        for (Item item : items) {
            cost += item.Price();
        }
        return cost;
    }

    public void ShowItems(){

        for (Item item : items) {
            System.out.print("Item : " + item.Name());
            System.out.print(", Packing : " + item.Packing().Pack());
            System.out.println(", Price : " + item.Price());
        }
    }
}