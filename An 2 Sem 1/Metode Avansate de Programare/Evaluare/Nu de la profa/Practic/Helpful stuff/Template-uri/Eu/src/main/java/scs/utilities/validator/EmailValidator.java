package scs.utilities.validator;

import java.util.regex.Pattern;

public class EmailValidator implements Validator<String> {
    private static final Pattern EMAIL = Pattern.compile("^[^@\\s]+@[^@\\s]+\\.[^@\\s]+$", Pattern.CASE_INSENSITIVE);

    @Override
    public void validate(String email) {
        if (email == null || !EMAIL.matcher(email).matches())
            throw new RuntimeException("email invalid.");
    }
}
