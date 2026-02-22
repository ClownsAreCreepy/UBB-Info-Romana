package scs.service;

import scs.domain.User;
import scs.repo.Repository;
import scs.repo.UserRepository;

public class UserService extends GenericService<User>{

    public UserService(Repository<User> repo) {
        super(repo);
    }

    public User login(String username, String password) {
        User user = ((UserRepository) repo).findByUsername(username);

        if (user != null && user.getPassword().equals(password))
            return user;

        return null;
    }
}
