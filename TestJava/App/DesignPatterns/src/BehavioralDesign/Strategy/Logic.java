package BehavioralDesign.Strategy;

/**
 * Created by justin on 2015-07-25.
 */

/*
    Strategy Pattern

    In Strategy pattern, a class behavior or its algorithm can be changed at run time.
    This type of design pattern comes under behavior pattern.

    In Strategy pattern, we create objects which represent various strategies
    and a context object whose behavior varies as per its strategy object.

    The strategy object changes the executing algorithm of the context object.

    Implementation

    We are going to create a Strategy interface defining an action
    and concrete strategy classes implementing the Strategy interface.

    Context is a class which uses a Strategy.

    StrategyPatternDemo, our demo class, will use Context
    and strategy objects to demonstrate change in Context behaviour based on strategy it deploys or uses.
 */


public class Logic {

    public static void Test() {

        Context context = new Context(new OperationAdd());
        System.out.println("10 + 5 = " + context.executeStrategy(10, 5));

        context = new Context(new OperationSubstract());
        System.out.println("10 - 5 = " + context.executeStrategy(10, 5));

        context = new Context(new OperationMultiply());
        System.out.println("10 * 5 = " + context.executeStrategy(10, 5));
    }
}
