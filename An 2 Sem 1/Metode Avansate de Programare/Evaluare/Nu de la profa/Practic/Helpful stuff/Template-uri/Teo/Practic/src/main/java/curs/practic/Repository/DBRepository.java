package curs.practic.Repository;
import curs.practic.Domain.Entity;
import curs.practic.Validators.Validator;

public abstract class DBRepository <ID, E extends Entity<ID>> implements Repository<ID, E> {
    private final String url;
    private final String username;
    private final String password;
    private final Validator<E> validator;

    public DBRepository(String url, String username, String password, Validator<E> validator) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
    }

    protected String getUrl() {
        return url;
    }

    protected String getUsername() {
        return username;
    }

    protected String getPassword() {
        return password;
    }

    protected Validator<E> getValidator() {
        return validator;
    }
}