/**
 * Created by justin on 2015-07-13.
 */

package Basic.Executor;

public class Result
{
    private int taskId;
    private int result;

    public Result( int taskId, int result ) {
        this.taskId = taskId;
        this.result = result;
    }

    public int GetTaskID() { return taskId; }

    public int GetResult() { return result; }

    public String ToString() {
        return "Task Name: Task #" + taskId + ", Task Result: " + result + " seconds";
    }
}
