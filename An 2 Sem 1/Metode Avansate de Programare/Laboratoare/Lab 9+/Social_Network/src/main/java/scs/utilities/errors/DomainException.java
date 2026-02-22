package scs.utilities.errors;

public class DomainException extends RuntimeException {
    private final String code;
    private final String field;

    public DomainException(String code, String field, String message) {
        super(message);
        this.code = code;
        this.field = field;
    }

    public String getCode() {
        return code;
    }

    public String getField() {
        return field;
    }
}
