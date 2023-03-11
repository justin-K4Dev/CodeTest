package BehavioralDesign.ChainOfResponsibility;

/**
 * Created by justin on 2015-07-24.
 */

public class ConsoleLogger extends AbstractLogger {

    public ConsoleLogger(int level){
        this.level = level;
    }

    @Override
    protected void write(String message) {
        System.out.println("Standard Console::Logger: " + message);
    }
}