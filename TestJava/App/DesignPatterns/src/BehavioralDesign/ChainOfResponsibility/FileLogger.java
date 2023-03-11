package BehavioralDesign.ChainOfResponsibility;

/**
 * Created by justin on 2015-07-24.
 */

public class FileLogger extends AbstractLogger {

    public FileLogger(int level){
        this.level = level;
    }

    @Override
    protected void write(String message) {
        System.out.println("File::Logger: " + message);
    }
}