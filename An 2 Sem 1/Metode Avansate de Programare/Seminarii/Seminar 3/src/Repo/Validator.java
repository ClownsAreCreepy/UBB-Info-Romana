package Repo;

public interface Validator<E>{
    void validate(E entity) throws ValidationException;
}
