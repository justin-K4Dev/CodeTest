package StructuralDesign.Filter;

/**
 * Created by justin on 2015-07-24.
 */

import java.util.List;
import java.util.ArrayList;

/*
    Filter Pattern

    Filter pattern or Criteria pattern is a design pattern
    that enables developers to filter a set of objects using different criteria
    and chaining them in a decoupled way through logical operations.

    This type of design pattern comes under structural pattern
    as this pattern combines multiple criteria to obtain single criteria.

    Implementation

    We're going to create a Person object,
    Criteria interface and concrete classes implementing this interface to filter list of Person objects.
    CriteriaPatternDemo, our demo class uses Criteria objects to filter List of Person objects based on various criteria
    and their combinations.
 */

public class Logic {

    public static void Test() {

        List<Person> persons = new ArrayList<Person>();

        persons.add(new Person("Robert","Male", "Single"));
        persons.add(new Person("John", "Male", "Married"));
        persons.add(new Person("Laura", "Female", "Married"));
        persons.add(new Person("Diana", "Female", "Single"));
        persons.add(new Person("Mike", "Male", "Single"));
        persons.add(new Person("Bobby", "Male", "Single"));

        Criteria male = new CriteriaMale();
        Criteria female = new CriteriaFemale();
        Criteria single = new CriteriaSingle();
        Criteria singleMale = new AndCriteria(single, male);
        Criteria singleOrFemale = new OrCriteria(single, female);

        System.out.println("Males: ");
        printPersons(male.meetCriteria(persons));

        System.out.println("\nFemales: ");
        printPersons(female.meetCriteria(persons));

        System.out.println("\nSingle Males: ");
        printPersons(singleMale.meetCriteria(persons));

        System.out.println("\nSingle Or Females: ");
        printPersons(singleOrFemale.meetCriteria(persons));
    }

    public static void printPersons(List<Person> persons){

        for (Person person : persons) {
            System.out.println("Person : [ Name : " + person.getName() + ", Gender : " + person.getGender() + ", Marital Status : " + person.getMaritalStatus() + " ]");
        }
    }
}
