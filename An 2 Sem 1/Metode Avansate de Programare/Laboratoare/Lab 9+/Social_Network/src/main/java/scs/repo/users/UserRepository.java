package scs.repo.users;

import scs.domain.user.User;
import scs.utilities.paging.Page;
import scs.utilities.paging.Pageable;

import java.util.Collection;
import java.util.List;

public interface UserRepository {
    void add(User user);               // create


    User findById(Long id);   // read

    User findByUsername(String username);

    User findByEmail(String email);

    List<User> getAll();

    List<User> findUsersByIds(Collection<Long> ids);

    Page<User> search(Pageable pageable, String typeFilter, String duckType, List<Long> includeIds, List<Long> excludeIds);


    void update(User user);            // update


    void deleteById(Long id);          // delete


    boolean existsById(Long id);
}
