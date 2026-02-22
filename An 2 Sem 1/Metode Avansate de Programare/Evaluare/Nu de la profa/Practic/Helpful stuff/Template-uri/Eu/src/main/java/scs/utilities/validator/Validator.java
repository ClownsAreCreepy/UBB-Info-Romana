package scs.utilities.validator;

@FunctionalInterface
public interface Validator<T> {
    void validate(T value);

    default Validator<T> and(Validator<T> other) {
        return v -> {
            this.validate(v);
            other.validate(v);
        };
    }

    static <T> Validator<T> optional(Validator<T> inner) {
        return v -> {
            if (v != null)
                inner.validate(v);
        };
    }
}