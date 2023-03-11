package StructuralDesign.Filter;

/**
 * Created by justin on 2015-07-24.
 */

import java.util.List;
import java.util.ArrayList;

public class CriteriaSingle implements Criteria {

    @Override
    public List<Person> meetCriteria( List<Person> persons ) {

        List<Person> singlePersons = new ArrayList<Person>();

        for (Person person : persons) {
            if(person.getMaritalStatus().equalsIgnoreCase("SINGLE")){
                singlePersons.add(person);
            }
        }
        return singlePersons;
    }
}