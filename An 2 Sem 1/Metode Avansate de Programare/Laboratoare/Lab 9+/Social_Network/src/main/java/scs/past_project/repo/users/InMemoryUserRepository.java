//package scs.repo.users;
//
//import scs.domain.user.User;
//import scs.utilities.errors.DuplicateException;
//import scs.utilities.errors.NotFoundException;
//
//import java.util.*;
//
//public class InMemoryUserRepository implements UserRepository {
//    private final Map<Long, User> data = new HashMap<>();
//    private final Map<String, Long> byUsername = new HashMap<>();
//    private final Map<String, Long> byEmail = new HashMap<>();
//
//    @Override
//    public void add(User user) {
//        // uniqueness
//        if (byUsername.containsKey(user.getUsername()))
//            throw new DuplicateException("username", "username already in use.");
//        if (byEmail.containsKey(user.getEmail()))
//            throw new DuplicateException("email", "email already in use.");
//
//        data.put(user.getId(), user);
//        byUsername.put(user.getUsername(), user.getId());
//        byEmail.put(user.getEmail(), user.getId());
//    }
//
//
//    @Override
//    public User findById(long id) {
//        User u = data.get(id);
//
//        if (u == null)
//            throw new NotFoundException("no id match", "user not found.");
//
//        return u;
//    }
//
//    @Override
//    public User findByUsername(String username) {
//        long uid = byUsername.get(username);
//        User u = data.get(uid);
//
//        if (u == null)
//            throw new NotFoundException("no id match", "user not found.");
//
//        return u;
//    }
//
//    @Override
//    public User findByEmail(String email) {
//        var u = Optional.ofNullable(byEmail.get(email)).map(data::get);
//
//        if (u.isEmpty())
//            throw new NotFoundException("no id match", "user not found.");
//
//        return u.get();
//    }
//
//    @Override
//    public List<User> getAll() {
//        return List.copyOf(data.values());
//    }
//
//
//    @Override
//    public void update(User user) {
//        var existing = data.get(user.getId());
//        if (existing == null)
//            throw new NotFoundException("no id match", "user does not exist.");
//
//        // rotate username index if changed
//        if (!Objects.equals(existing.getUsername(), user.getUsername())) {
//            if (byUsername.containsKey(user.getUsername()))
//                throw new DuplicateException("username", "username already in use.");
//
//            byUsername.remove(existing.getUsername());
//            byUsername.put(user.getUsername(), user.getId());
//        }
//
//        // rotate email index if changed
//        if (!Objects.equals(existing.getEmail(), user.getEmail())) {
//            if (byEmail.containsKey(user.getEmail()))
//                throw new DuplicateException("email", "email already in use.");
//
//            byEmail.remove(existing.getEmail());
//            byEmail.put(user.getEmail(), user.getId());
//        }
//
//        data.put(user.getId(), user);
//    }
//
//    @Override
//    public void deleteById(long id) {
//        User u = data.remove(id);
//        if (u == null)
//            throw new NotFoundException("no id match", "user does not exist.");
//
//        byUsername.remove(u.getUsername());
//        byEmail.remove(u.getEmail());
//    }
//
//    @Override
//    public boolean existsById(long id) {
//        return data.containsKey(id);
//    }
//}
