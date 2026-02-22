package curs.practic.Repository;


import curs.practic.Domain.Entity;
import curs.practic.Util.paging.Page;
import curs.practic.Util.paging.Pageable;

public interface PagingRepository<ID , E extends Entity<ID>> extends Repository<ID, E> {
    Page<E> findAllOnPage(Pageable pageable);
}
