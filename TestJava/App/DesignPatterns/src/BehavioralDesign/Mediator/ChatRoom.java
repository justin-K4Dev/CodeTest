package BehavioralDesign.Mediator;

/**
 * Created by justin on 2015-07-24.
 */

import java.util.Date;

public class ChatRoom {
    public static void showMessage(User user, String message){
        System.out.println(new Date().toString() + " [" + user.getName() + "] : " + message);
    }
}