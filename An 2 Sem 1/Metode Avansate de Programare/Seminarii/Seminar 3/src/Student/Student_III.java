package Student;

import Repo.Entity;

import java.util.Objects;

public class Student_III implements Entity<Integer> {
    private Integer id;
    private String nume;
    private float media;

    public Student_III(Integer id, String nume, float media) {
        this.id = id;
        this.nume = nume;
        this.media = media;
    }

    @Override
    public String toString() {
        return "Student {id='" + id + ", nume='" + nume + "', media='" + media + '}';
    }

    // defines what makes 2 students "equal"
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true; // same memory
        if (!(obj instanceof Student_III s)) return false;
        return Objects.equals(id, s.getId());
    }

    // used by HashSet/HashMap
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }


    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer id) {
        this.id = id;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public float getMedia() {
        return media;
    }

    public void setMedia(float media) {
        this.media = media;
    }
}
