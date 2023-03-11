package BehavioralDesign.ChainOfResponsibility;

/**
 * Created by justin on 2015-07-24.
 */

public class ErrorLogger extends AbstractLogger {

    public ErrorLogger(int level){
        this.level = level;
    }

    @Override
    protected void write(String message) {
        System.out.println("Error Console::Logger: " + message);
    }
}