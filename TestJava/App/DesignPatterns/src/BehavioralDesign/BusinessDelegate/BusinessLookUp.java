package BehavioralDesign.BusinessDelegate;

/**
 * Created by justin on 2015-07-25.
 */

public class BusinessLookUp {
    public BusinessService getBusinessService(String serviceType){

        if(serviceType.equalsIgnoreCase("EJB")){
            return new EJBService();
        }
        else {
            return new JMSService();
        }
    }
}