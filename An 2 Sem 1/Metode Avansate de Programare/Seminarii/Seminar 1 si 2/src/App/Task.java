package App;

import java.util.Objects;

public abstract class Task {
    private int id;
    private String descriere;

    // constructor
    public Task(int id, String descriere) {
        this.id = id;
        this.descriere = descriere;
    }

    // getters and setters
    public int getID() {
        return id;
    }

    public void setID(int new_id) {
        this.id = new_id;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String new_descriere) {
        this.descriere = new_descriere;
    }

    // abstract method (no body, subclass must define it)
    public abstract void execute();

    // toString
    @Override
    public String toString() {
        return "App.Task{" +
                "id='" + id + '\'' +
                ", descriere='" + descriere + '\'' +
                '}';
    }

    // equals & hashCode - important for collections
    @Override
    public boolean equals(Object o) {
        if (this == o) return true; // same object
        if (o == null || getClass() != o.getClass()) return false; // verifica tipul de task
        Task task = (Task) o;
        return Objects.equals(id, task.id) && Objects.equals(descriere, task.descriere);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, descriere);
    }
}
