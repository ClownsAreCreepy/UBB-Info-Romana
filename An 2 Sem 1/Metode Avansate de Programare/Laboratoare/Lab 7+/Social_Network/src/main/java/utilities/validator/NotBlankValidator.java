package utilities.validator;

import utilities.errors.ValidationException;

public class NotBlankValidator implements Validator<String> {
    private final String fieldName;

    public NotBlankValidator(String fieldName) {
        this.fieldName = fieldName;
    }

    @Override
    public void validate(String value) {
        if (value == null || value.trim().isEmpty())
            throw new ValidationException(fieldName, fieldName + "nu poate fi gol.");
    }
}
