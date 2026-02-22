package service;

import domain.user.*;
import repo.users.UserRepository;
import utilities.*;
import utilities.validator.*;

import java.time.LocalDate;
import java.util.List;

public class UserService {
    private final UserRepository repo;
    private final IdGenerator ids = new  IdGenerator();
    private final Validator<String> emailValidator = new EmailValidator();

    public UserService(UserRepository repo) {
        this.repo = repo;
    }

    private void validateUser(String username, String email, String password){
        new NotBlankValidator("username").validate(username);
        new NotBlankValidator("password").validate(password);
        emailValidator.validate(email);

        V.maxLengthString("username", 30).validate(username);
        V.maxLengthString("email", 30).validate(email);
    }

    public Person createPerson(String username, String email, String password,
                             String nume, String prenume, LocalDate dataN, String ocupatie) {
        validateUser(username, email, password);

        V.maxLengthString("nume", 50).validate(nume);
        V.maxLengthString("prenume", 50).validate(prenume);
        new TimeValidator("birth date", LocalDate.now().minusYears(100), LocalDate.now()).validate(dataN);
        V.maxLengthString("ocupatie", 50).validate(ocupatie);

        var p = new Person(ids.next(), username, email, password, nume, prenume, dataN, ocupatie);
        repo.add(p);
        return p;
    }

    public SwimmingDuck createSwimmingDuck(String username, String email, String password,
                                   double viteza, double rezistenta) {
        validateUser(username, email, password);

        V.minLengthDouble("viteza", 0).validate(viteza);
        V.minLengthDouble("rezistenta", 0).validate(rezistenta);

        var d = new SwimmingDuck(ids.next(), username, email, password, viteza, rezistenta);
        repo.add(d);
        return d;
    }

    public FlyingDuck createFlyingDuck(String username, String email, String password,
                                            double viteza, double rezistenta) {
        validateUser(username, email, password);

        V.minLengthDouble("viteza", 0).validate(viteza);
        V.minLengthDouble("rezistenta", 0).validate(rezistenta);

        var d = new FlyingDuck(ids.next(), username, email, password, viteza, rezistenta);
        repo.add(d);
        return d;
    }

    public HybridDuck createHybridDuck(String username, String email, String password,
                                   double viteza, double rezistenta) {
        validateUser(username, email, password);

        V.minLengthDouble("viteza", 0).validate(viteza);
        V.minLengthDouble("rezistenta", 0).validate(rezistenta);

        var d = new HybridDuck(ids.next(), username, email, password, viteza, rezistenta);
        repo.add(d);
        return d;
    }

    public void deleteUser(long id) {
        repo.deleteById(id);
    }

    public List<User> getAll() {
        return repo.getAll();
    }

    public User findById(long id) {
        return repo.findById(id);
    }
}
