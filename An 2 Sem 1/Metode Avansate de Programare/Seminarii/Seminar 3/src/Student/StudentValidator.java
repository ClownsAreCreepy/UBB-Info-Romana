package Student;

import Repo.ValidationException;
import Repo.Validator;

public class StudentValidator implements Validator<Student_III> {
    @Override
    public void validate(Student_III s) {
        if (s == null) throw new ValidationException("student null");
        if (s.getNume() == null || s.getNume().isBlank()) throw new ValidationException("nume invalid");
        if (s.getMedia() < 0f || s.getMedia() > 10f) throw new ValidationException("media must be between 0 and 10");
    }
}
