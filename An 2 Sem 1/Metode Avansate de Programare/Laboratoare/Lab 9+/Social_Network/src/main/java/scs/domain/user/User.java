package scs.domain.user;

public abstract class User {
    protected final Long id;
    protected final String username;
    protected final String email;
    protected String password;

    protected User(Long id, String username, String email, String password) {
        this.id = id;
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public Long getId() {
        return id;
    }

    public String getUsername() {
        return username;
    }

    public String getEmail() {
        return email;
    }

    public String getPassword() {       // returns hash
        return password;
    }

    public void setPassword(String hashedPassword) {
        this.password = hashedPassword;
    }

    @Override
    public String toString() {
        return "%s{id=%d, user=%s}".formatted(getClass().getSimpleName(), id, username);
    }

    @Override
    public boolean equals(Object o) {
        return (o instanceof User u) && u.id.equals(id);
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }
}
