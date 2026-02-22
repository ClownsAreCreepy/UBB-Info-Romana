public class Examen {
    private String studentName;
    private String subject;
    private double grade;

    public Examen(String studentName, String subject, double grade) {
        this.studentName = studentName;
        this.subject = subject;
        this.grade = grade;
    }

    public String getStudentName() {
        return studentName;
    }

    public String getSubject() {
        return subject;
    }

    public double getGrade() {
        return grade;
    }

    @Override
    public String toString() {
        return studentName + " - " +  subject + " : " + grade;
    }
}