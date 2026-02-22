package utilities.validator;

import error.ValidationException;

public final class V {
    private V() {
    }

    public static Validator<Double> maxLengthDouble(String field, long max) {
        return v -> {
            if (v != null && v > max)
                throw new ValidationException(field, field + " must be < " + max);
        };
    }

    public static Validator<Integer> maxLengthInt(String field, long max) {
        return v -> {
            if (v != null && v > max)
                throw new ValidationException(field, field + " must be < " + max);
        };
    }

    public static Validator<String> maxLengthString(String field, long max) {
        return v -> {
            if (v != null && v.length() > max)
                throw new ValidationException(field, field + " must be < " + max);
        };
    }

    public static Validator<Double> minLengthDouble(String field, long min) {
        return v -> {
            if (v != null && v < min)
                throw new ValidationException(field, field + " must be > " + min);
        };
    }

    public static Validator<Integer> minLengthInt(String field, long min) {
        return v -> {
            if (v != null && v < min)
                throw new ValidationException(field, field + " must be > " + min);
        };
    }

    public static Validator<String> minLengthString(String field, long min) {
        return v -> {
            if (v != null && v.length() < min)
                throw new ValidationException(field, field + " must be > " + min);
        };
    }
}
