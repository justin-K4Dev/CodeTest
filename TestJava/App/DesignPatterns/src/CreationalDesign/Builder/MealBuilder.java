package CreationalDesign.Builder;

/**
 * Created by justin on 2015-07-24.
 */

public class MealBuilder {

    public Meal prepareVegMeal (){
        Meal meal = new Meal();
        meal.AddItem(new VegBurger());
        meal.AddItem(new Coke());
        return meal;
    }

    public Meal prepareNonVegMeal (){
        Meal meal = new Meal();
        meal.AddItem(new ChickenBurger());
        meal.AddItem(new Pepsi());
        return meal;
    }
}
