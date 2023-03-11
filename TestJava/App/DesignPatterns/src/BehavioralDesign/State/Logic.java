package BehavioralDesign.State;

/**
 * Created by justin on 2015-07-24.
 */

/*
    State Pattern

    In State pattern a class behavior changes based on its state.
    This type of design pattern comes under behavior pattern.

    In State pattern, we create objects which represent various states
    and a context object whose behavior varies as its state object changes.

    Implementation

    We are going to create a State interface defining an action
    and concrete state classes implementing the State interface.

    Context is a class which carries a State.

    StatePatternDemo, our demo class, will use Context
    and state objects to demonstrate change in Context behavior based on type of state it is in.
 */

public class Logic {

    public static void Test() {

        Context context = new Context();

        StartState startState = new StartState();
        startState.doAction(context);

        System.out.println(context.getState().toString());

        StopState stopState = new StopState();
        stopState.doAction(context);

        System.out.println(context.getState().toString());
    }
}
