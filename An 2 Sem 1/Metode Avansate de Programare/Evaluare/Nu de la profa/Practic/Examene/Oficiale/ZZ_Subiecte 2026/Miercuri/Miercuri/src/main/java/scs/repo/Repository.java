package scs.repo;

import scs.utilities.paging.Page;
import scs.utilities.paging.Pageable;

import java.util.List;
import java.util.Optional;

public interface Repository<E> {
    E save(E entity);
    Optional<E> findOne(Long id);
    void update(E entity);
    void delete(Long id);
    List<E> findAll();
    Page<E> findAll(Pageable pageable);
}