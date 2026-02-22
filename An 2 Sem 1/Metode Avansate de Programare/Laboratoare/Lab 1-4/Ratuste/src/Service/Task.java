package Service;

import java.util.Objects;

public abstract class Task {
    private String TaskID;
    private String Descriere;

    public String getTaskID() {
        return TaskID;
    }

    public void setTaskID(String taskID) {
        TaskID = taskID;
    }

    public String getDescriere() {
        return Descriere;
    }

    public void setDescriere(String descriere) {
        Descriere = descriere;
    }

    public abstract void execute(); // will run the task


    @Override
    public String toString() {
        return TaskID + " - " + Descriere;
    }

    @Override
    public int hashCode() {
        return (TaskID == null ? 0 : TaskID.hashCode());
    }

    @Override
    public boolean equals(Object o) {
        if (!(o instanceof Task task)) return false;
        return Objects.equals(TaskID, task.TaskID);
    }
}
