package scs.domain.user;

import java.time.LocalDate;
import java.time.Period;

public class Person extends User {
    private final String name;
    private final String firstName;
    private final LocalDate birthDate;
    private final String occupation;

    private Person(Builder builder) {
        super(builder.id, builder.username, builder.email, builder.password);
        this.name = builder.name;
        this.firstName = builder.firstName;
        this.birthDate = builder.birthDate;
        this.occupation = builder.occupation;
    }

    public static class Builder {
        private final Long id;
        private String username;
        private String email;
        private String password;

        private String name;
        private String firstName;
        private LocalDate birthDate;
        private String occupation;

        public Builder(Long id) {
            this.id = id;
        }

        public Builder username(String username) {
            this.username = username;
            return this;
        }

        public Builder email(String email) {
            this.email = email;
            return this;
        }

        public Builder password(String hash) {
            this.password = hash;
            return this;
        }

        public Builder name(String name) {
            this.name = name;
            return this;
        }

        public Builder firstName(String firstName) {
            this.firstName = firstName;
            return this;
        }

        public Builder birthDate(LocalDate birthDate) {
            this.birthDate = birthDate;
            return this;
        }

        public Builder occupation(String occupation) {
            this.occupation = occupation;
            return this;
        }

        public Person build() {
            return new Person(this);
        }

    }

    public String getName() {
        return name;
    }

    public String getFirstName() {
        return firstName;
    }

    public LocalDate getBirthDate() {
        return birthDate;
    }

    public String getOccupation() {
        return occupation;
    }

    public String getFullName() {
        return (name + " " + firstName).trim();
    }

    public int getAge() {
        return Period.between(birthDate, LocalDate.now()).getYears();
    }
}
