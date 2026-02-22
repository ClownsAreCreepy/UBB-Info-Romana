package com.example.template.domeniu;

public class Persoana extends Entity<Long>{
    private String username;
    private String nume;
    public Persoana(String username, String nume) {
        this.username=username;
        this.nume=nume;
    }
    public String getUsername() {
        return username;
    }
    public String getNume() {
        return nume;
    }
    public void setNume(String nume) {
        this.nume = nume;
    }
    public void setUsername(String username) {
        this.username = username;
    }

    @Override
    public String toString() {
        return "Persoana{" +
                "username='" + username + '\'' +
                ", nume='" + nume + '\'' +
                '}';
    }
}
