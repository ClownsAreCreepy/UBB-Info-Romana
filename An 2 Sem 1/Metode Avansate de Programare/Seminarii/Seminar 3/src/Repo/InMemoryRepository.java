package Repo;

import java.util.*;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository0<ID, E> {
    private final Map<ID, E> storage = new HashMap<>();
    private final Validator<E> validator;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
    }

    @Override
    public E findOne(ID id) {
        if (id == null) throw new IllegalArgumentException("ID must not be null!");
        return storage.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return storage.values();
    }

    @Override
    public E save(E entity) {
        if (entity == null) throw new IllegalArgumentException("Entity must not be null!");
        validator.validate(entity);

        ID id = entity.getId();
        if (id == null) throw new IllegalArgumentException("ID must not be null!");

        // spec: return null if saved; otherwise return the entity (id already exists)
        if (storage.containsKey(id))
            return entity;

        storage.put(id, entity);
        return null;
    }

    @Override
    public E delete(ID id) {
        if (id == null) throw new IllegalArgumentException("ID must not be null!");
        return storage.remove(id);
    }

    @Override
    public E update(E entity) {
        if (entity == null) throw new IllegalArgumentException("Entity must not be null!");
        validator.validate(entity);

        ID id = entity.getId();
        if (id == null) throw new IllegalArgumentException("ID must not be null!");

        // spec: return null if updated; otherwise return entity (id does not exist)
        if (!storage.containsKey(id))
            return entity;

        storage.put(id, entity);
        return null;
    }
}
