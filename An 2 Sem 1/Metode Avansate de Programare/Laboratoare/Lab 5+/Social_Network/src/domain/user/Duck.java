package domain.user;

public class Duck extends User {
    private final double viteza;
    private final double rezistenta;

    public Duck(long id, String username, String email, String password,
                double viteza, double rezistenta) {
        super(id, username, email, password);
        this.viteza = viteza;
        this.rezistenta = rezistenta;
    }

    public double getViteza() {
        return viteza;
    }

    public double getRezistenta() {
        return rezistenta;
    }
}
