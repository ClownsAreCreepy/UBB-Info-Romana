public class Nota {
    private final Student student;
    private final Tema tema;
    private final String subject;
    private final double value;
    private final String profesor;
    private AssessmentType type;

    // homework ctor
    public Nota(Student student, Tema tema, double value, String profesor) {
        this.student = student;
        this.tema = tema;
        this.subject = tema.getDescriere();
        this.value = value;
        this.profesor = profesor;
        this.type = AssessmentType.HOMEWORK;
    }

    public Nota(Student student, String subject, double value, String profesor, AssessmentType type) {
        this.student = student;
        this.tema = null;
        this.subject = subject;
        this.value = value;
        this.profesor = profesor;
        this.type = type;
    }

    public Student getStudent() {
        return student;
    }

    public Tema getTema() {
        return tema;
    }

    public String getSubject() {
        return subject;
    }

    public double getValue() {
        return value;
    }

    public String getProfesor() {
        return profesor;
    }

    public AssessmentType getType() {
        return type;
    }

    @Override
    public String toString() {
        return "Nota{" +
                "student=" + student +
                ", tema=" + tema +
                ", value=" + value +
                ", profesor='" + profesor + '\'' +
                '}';
    }
}
