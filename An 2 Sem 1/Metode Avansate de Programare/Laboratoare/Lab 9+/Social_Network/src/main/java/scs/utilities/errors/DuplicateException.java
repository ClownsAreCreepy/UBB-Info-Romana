package scs.utilities.errors;

public class DuplicateException extends DomainException {
    public DuplicateException(String field, String message) {
        super("duplicate", field, message);
    }
}
