package BehavioralDesign.DataAccessObject;

/**
 * Created by justin on 2015-07-25.
 */

import java.util.List;

public interface StudentDao {
    public List<Student> getAllStudents();
    public Student getStudent(int rollNo);
    public void updateStudent(Student student);
    public void deleteStudent(Student student);
}