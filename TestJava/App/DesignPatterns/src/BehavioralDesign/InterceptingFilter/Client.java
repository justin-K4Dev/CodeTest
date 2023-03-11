package BehavioralDesign.InterceptingFilter;

/**
 * Created by justin on 2015-07-25.
 */

public class Client {
    FilterManager filterManager;

    public void setFilterManager(FilterManager filterManager){
        this.filterManager = filterManager;
    }

    public void sendRequest(String request){
        filterManager.filterRequest(request);
    }
}