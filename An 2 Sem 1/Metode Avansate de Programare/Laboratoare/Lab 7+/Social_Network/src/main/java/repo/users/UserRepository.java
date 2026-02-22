package repo.users;

import domain.user.User;

import java.util.List;

public interface UserRepository {
    void add(User user);               // create

    User findById(long id);   // read
    User findByUsername(String username);
    User findByEmail(String email);
    List<User> getAll();

    void update(User user);            // update

    void deleteById(long id);          // delete

    boolean existsById(long id);
}
