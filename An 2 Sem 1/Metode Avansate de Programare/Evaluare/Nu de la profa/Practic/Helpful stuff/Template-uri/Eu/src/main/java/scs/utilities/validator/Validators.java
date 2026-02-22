package scs.utilities.validator;

public final class Validators {
    private Validators() {
    }

    public static <T extends Comparable<T>> Validator<T> maxValue(String field, T max) {
        return v -> {
            if (v != null && v.compareTo(max) > 0)
                throw new RuntimeException(field + " must be <= " + max);
        };
    }

    public static Validator<String> maxLength(String field, long max) {
        return v -> {
            if (v != null && v.length() > max)
                throw new RuntimeException(field + " length must be < " + max);
        };
    }

    public static <T extends Comparable<T>> Validator<T> minValue(String field, T min) {
        return v -> {
            if (v != null && v.compareTo(min) < 0)
                throw new RuntimeException(field + " must be >= " + min);
        };
    }

    public static Validator<String> minLength(String field, long min) {
        return v -> {
            if (v != null && v.length() < min)
                throw new RuntimeException(field + " length must be >= " + min);
        };
    }
}
