package error;

public class DuplicateException extends DomainException {
    public DuplicateException(String field, String message) {
        super("duplicate", field, message);
    }
}
