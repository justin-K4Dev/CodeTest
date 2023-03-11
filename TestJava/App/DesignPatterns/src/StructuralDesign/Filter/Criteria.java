package StructuralDesign.Filter;

/**
 * Created by justin on 2015-07-24.
 */

import java.util.List;

public interface Criteria {

    public List<Person> meetCriteria( List<Person> persons );
}
