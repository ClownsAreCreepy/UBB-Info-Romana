package scs.service.social;

import org.mindrot.jbcrypt.BCrypt;
import scs.domain.user.*;
import scs.repo.users.UserRepository;
import scs.utilities.*;
import scs.utilities.errors.ValidationException;
import scs.utilities.events.ChangeEventType;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observable;
import scs.utilities.validator.*;
import scs.utilities.paging.*;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Set;

public class UserService extends Observable<EntityChangeEvent<User>> {
    public static final Long RACE_BOT_ID = 0L;
    private final UserRepository repo;
    private final IdGenerator ids;
    private final Validator<String> emailValidator = new EmailValidator();

    public UserService(UserRepository repo, IdGenerator ids) {
        this.repo = repo;
        this.ids = ids;
    }

    private String hashPassword(String plainPassword) {
        return BCrypt.hashpw(plainPassword, BCrypt.gensalt());
    }

    private void validateUser(String username, String email, String password) {
        new NotBlankValidator("username").validate(username);
        new NotBlankValidator("password").validate(password);
        emailValidator.validate(email);

        Validators.maxLength("username", 30).validate(username);
        Validators.maxLength("email", 30).validate(email);
    }

    public Person createPerson(String username, String email, String password,
                               String name, String firstName, LocalDate birthD, String occupation) {
        validateUser(username, email, password);

        Validators.maxLength("name", 50).validate(name);
        Validators.maxLength("firstName", 50).validate(firstName);
        new TimeValidator("birth date", LocalDate.now().minusYears(100), LocalDate.now()).validate(birthD);
        Validators.maxLength("occupation", 50).validate(occupation);

        String passwordHash = hashPassword(password);

        Person p = new Person.Builder(ids.next())
                .username(username)
                .email(email)
                .password(passwordHash)
                .name(name)
                .firstName(firstName)
                .birthDate(birthD)
                .occupation(occupation)
                .build();

        repo.add(p);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADD, p));

        return p;
    }

    public SwimmingDuck createSwimmingDuck(String username, String email, String password,
                                           double speed, double resistance) {
        validateUser(username, email, password);

        Validators.minValue("speed", 0.0).validate(speed);
        Validators.minValue("resistance", 0.0).validate(resistance);

        SwimmingDuck d = new SwimmingDuck(ids.next(), username, email, hashPassword(password), speed, resistance);
        repo.add(d);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADD, d));

        return d;
    }

    public FlyingDuck createFlyingDuck(String username, String email, String password,
                                       double speed, double resistance) {
        validateUser(username, email, password);

        Validators.minValue("speed", 0.0).validate(speed);
        Validators.minValue("resistance", 0.0).validate(resistance);

        FlyingDuck d = new FlyingDuck(ids.next(), username, email, hashPassword(password), speed, resistance);
        repo.add(d);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADD, d));

        return d;
    }

    public HybridDuck createHybridDuck(String username, String email, String password,
                                       double speed, double resistance) {
        validateUser(username, email, password);

        Validators.minValue("speed", 0.0).validate(speed);
        Validators.minValue("resistance", 0.0).validate(resistance);

        HybridDuck d = new HybridDuck(ids.next(), username, email, hashPassword(password), speed, resistance);
        repo.add(d);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADD, d));

        return d;
    }

    public void modifyUser(User user) {
        // Superficial validation just for the observer, so it's ok that it's barebones
        // We don't modify users in this app just yet
        validateUser(user.getUsername(), user.getEmail(), user.getPassword());

        repo.update(user);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE, user));
    }

    public void deleteUser(Long id) {
        User deletedUser = repo.findById(id);

        repo.deleteById(id);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.DELETE, deletedUser));
    }

    public List<User> getAll() {
        return repo.getAll();
    }

    public User findById(Long id) {
        return repo.findById(id);
    }

    public List<User> findUsersByIds(Collection<Long> ids) {
        return repo.findUsersByIds(ids);
    }

    public Page<User> searchUsers(Pageable pageable, String userType, String duckType,
                                  String relationFilter, Long currentUserId, Set<Long> friendIds) {
        List<Long> include = new ArrayList<>();
        List<Long> exclude = new ArrayList<>();

        // Exclusions
        exclude.add(currentUserId);
        exclude.add(RACE_BOT_ID);

        switch (relationFilter) {
            case "FRIENDS" -> {
                if (friendIds.isEmpty())
                    return new Page<>(List.of(), 0, pageable.getPageSize());
                include.addAll(friendIds);
            }
            case "NOT FRIENDS" -> {
                exclude.addAll(friendIds);
            }
            case "ALL" -> {

            }
        }
        return repo.search(pageable, userType, duckType, include, exclude);
    }

    public User login(String email, String password) {
        if (email == null || email.isBlank())
            throw new ValidationException("login email", "Email cannot be empty.");
        if (password == null || password.isBlank())
            throw new ValidationException("login password", "Password cannot be empty.");

        User user = repo.findByEmail(email);

        if (!BCrypt.checkpw(password, user.getPassword()))
            throw new ValidationException("login", "Invalid email or password");

        return user;
    }

}

//    public Page<User> findAll(Pageable pageable) {
//        Validators.minValue("page size", 1).and(Validators.maxValue("page size", 100)).validate(pageable.getPageSize());
//        Validators.minValue("page value", 0).validate(pageable.getPageNumber());
//
//        return repo.findAll(pageable);
//    }
//
//    public Page<Duck> findAllDucks(Pageable pageable, String type) {
//        Validators.minValue("page size", 1).and(Validators.maxValue("page size", 100)).validate(pageable.getPageSize());
//        Validators.minValue("page value", 0).validate(pageable.getPageNumber());
//
//        return repo.findAllDucks(pageable, type);
//    }
//
//    public Page<Person> findAllPeople(Pageable pageable) {
//        Validators.minValue("page size", 1).and(Validators.maxValue("page size", 50)).validate(pageable.getPageSize());
//        Validators.minValue("page value", 0).validate(pageable.getPageNumber());
//
//        return repo.findAllPeople(pageable);
//    }
//
//    public List<Duck> filterDucks(String t) {
//
//        return getAll().stream()
//                .filter(u -> u instanceof Duck)
//                .map(u -> (Duck) u)
//                .filter(d -> {
//                    if (t == null || t.equals("ALL"))
//                        return true;
//                    return switch (t) {
//                        case "SWIMMING" -> d instanceof SwimmingDuck;
//                        case "FLYING" -> d instanceof FlyingDuck;
//                        case "HYBRID" -> d instanceof HybridDuck;
//                        default -> true;
//                    };
//                })
//                .collect(Collectors.toList());
//    }