package scs.domain.user;

public abstract class Duck extends User {
    private final double speed;
    private final double resistance;

    public Duck(Long id, String username, String email, String password,
                double speed, double resistance) {
        super(id, username, email, password);
        this.speed = speed;
        this.resistance = resistance;
    }

    public double getSpeed() {
        return speed;
    }

    public double getResistance() {
        return resistance;
    }

}
