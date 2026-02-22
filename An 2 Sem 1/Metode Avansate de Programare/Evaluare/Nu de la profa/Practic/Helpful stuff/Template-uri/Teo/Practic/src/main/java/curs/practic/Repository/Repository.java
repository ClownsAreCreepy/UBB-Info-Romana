package curs.practic.Repository;

import curs.practic.Domain.Entity;
import curs.practic.Exceptions.RepositoryException;
import curs.practic.Exceptions.ValidationException;

/**
 * CRUD operations repository interface
 *
 * @param <ID> - type E must have an attribute of type ID
 * @param <E>  -  type of entities saved in repository
 */

public interface Repository<ID, E extends Entity<ID>> {

    /**
     *
     * @param id -the id of the entity to be returned
     *           id must not be null
     * @return the entity with the specified id
     * or null - if there is no entity with the given id
     * @throws RepositoryException if id is null.
     */
    E findOne(ID id);

    /**
     *
     * @return all entities
     */
    Iterable<E> findAll();

    /**
     * @param entity entity must be not null
     * @return null- if the given entity is saved
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if the given entity is null.
     * @throws RepositoryException if the entity already exists
     */
    E save(E entity);

    /**
     * removes the entity with the specified id
     * @param id id must be not null
     * @return the removed entity
     * @throws RepositoryException if the given id is null.
     * @throws RepositoryException if there is no entity with the given id
     */
    E delete(ID id);

    /**
     *
     * @param entity entity must not be null
     * @return null - if the entity is updated,
     * otherwise  returns the entity  - (e.g. id does not exist).
     * @throws RepositoryException the given entity is null.
     * @throws RepositoryException the given entity does not exist.
     * @throws ValidationException      if the entity is not valid.
     */
    E update(E entity);
}


