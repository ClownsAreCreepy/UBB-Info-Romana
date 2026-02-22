package scs.utilities.errors;

public class NotFoundException extends DomainException {
    public NotFoundException(String what, String message) {
        super("not found", what, message);
    }
}
