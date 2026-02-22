package scs.utilities.validator;

import scs.utilities.errors.ValidationException;

public final class Validators {
    private Validators() {
    }

    public static <T extends Comparable<T>> Validator<T> maxValue(String field, T max) {
        return v -> {
            if (v != null && v.compareTo(max) > 0)
                throw new ValidationException(field, field + " must be <= " + max);
        };
    }

    public static Validator<String> maxLength(String field, long max) {
        return v -> {
            if (v != null && v.length() > max)
                throw new ValidationException(field, field + " length must be < " + max);
        };
    }

    public static <T extends Comparable<T>> Validator<T> minValue(String field, T min) {
        return v -> {
            if (v != null && v.compareTo(min) < 0)
                throw new ValidationException(field, field + " must be >= " + min);
        };
    }

    public static Validator<String> minLength(String field, long min) {
        return v -> {
            if (v != null && v.length() < min)
                throw new ValidationException(field, field + " length must be >= " + min);
        };
    }
}
