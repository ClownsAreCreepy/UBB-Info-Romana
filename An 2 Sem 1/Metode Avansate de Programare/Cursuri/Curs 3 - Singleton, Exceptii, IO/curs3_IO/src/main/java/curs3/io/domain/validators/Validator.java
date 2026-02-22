package curs3.io.domain.validators;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}