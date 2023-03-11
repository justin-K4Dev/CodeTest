package BehavioralDesign.BusinessDelegate;

/**
 * Created by justin on 2015-07-25.
 */

public class Client {

    BusinessDelegate businessService;

    public Client(BusinessDelegate businessService){
        this.businessService  = businessService;
    }

    public void doTask(){
        businessService.doTask();
    }
}