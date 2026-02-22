package scs.utilities.errors;

public class DatabaseException extends DomainException {
    public DatabaseException(String what, String message) {
        super("SQL problem", what, message);
    }
}
