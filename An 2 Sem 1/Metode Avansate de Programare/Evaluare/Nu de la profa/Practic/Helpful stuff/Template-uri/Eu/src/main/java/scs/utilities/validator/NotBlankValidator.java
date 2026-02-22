package scs.utilities.validator;

public class NotBlankValidator implements Validator<String> {
    private final String fieldName;

    public NotBlankValidator(String fieldName) {
        this.fieldName = fieldName;
    }

    @Override
    public void validate(String value) {
        if (value == null || value.trim().isEmpty())
            throw new RuntimeException(fieldName + " cannot be empty.");
    }
}
