package domain.user;

import java.time.LocalDate;
import java.time.Period;

public class Person extends User {
    private final String nume;
    private final String prenume;
    private final LocalDate dataNasterii;
    private final String ocupatie;

    public Person(long id, String username, String email, String password,
                  String nume, String prenume, LocalDate dataNasterii, String ocupatie){
        super(id, username, email, password);
        this.nume = nume;
        this.prenume = prenume;
        this.dataNasterii = dataNasterii;
        this.ocupatie = ocupatie;
    }

    public String getNume() {
        return nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public LocalDate getDataNasterii() {
        return dataNasterii;
    }

    public String getOcupatie() {
        return ocupatie;
    }

    public String getFullName() {
        return (nume + " " + prenume).trim();
    }

    public int getAge() {
        return Period.between(dataNasterii, LocalDate.now()).getYears();
    }
}
