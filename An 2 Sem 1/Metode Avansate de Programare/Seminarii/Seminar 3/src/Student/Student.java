package Student;

import java.util.Objects;

public class Student {
    private String nume;
    private float media;

    public Student(String nume, float media) {
        this.nume = nume;
        this.media = media;
    }

    @Override
    public String toString() {
        return "Student.Student {nume='" + nume + "', media='" + media + '}';
    }

    // defines what makes 2 students "equal"
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true; // same memory
        if (obj == null || getClass() != obj.getClass()) return false;
        Student s = (Student) obj;
        return Float.compare(s.media, media) == 0 && nume.equals(s.nume);
    }

    // used by HashSet/HashMap
    @Override
    public int hashCode() {
        return Objects.hash(nume, media);
    }

    public String getNume() {
        return nume;
    }

    public float getMedia() {
        return media;
    }
}
