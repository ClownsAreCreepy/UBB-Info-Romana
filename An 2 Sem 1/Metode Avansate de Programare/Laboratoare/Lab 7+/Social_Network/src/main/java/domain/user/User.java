package domain.user;

import java.util.Objects;

public abstract class User {
    protected final long id;
    protected final String username;
    protected final String email;
    protected String password;

    protected User(long id, String username, String email, String password) {
        this.id = id;
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public long getId() {
        return id;
    }

    public String getUsername() {
        return username;
    }

    public String getEmail() {
        return email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = Objects.requireNonNull(password);
    }

    @Override
    public String toString() {
        return "%s{id=%d, user=%s}".formatted(getClass().getSimpleName(), id, username);
    }

    @Override
    public boolean equals(Object o) {
        return (o instanceof User u) && u.id == id;
    }

    @Override
    public int hashCode() {
        return Long.hashCode(id);
    }
}
