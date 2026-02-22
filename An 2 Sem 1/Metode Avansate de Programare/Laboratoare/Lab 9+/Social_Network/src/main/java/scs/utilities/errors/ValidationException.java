package scs.utilities.errors;

public class ValidationException extends DomainException {
    public ValidationException(String field, String message) {
        super("validation", field, message);
    }
}
