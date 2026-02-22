package domain.user;

import domain.behaviors.Inotator;

public class SwimmingDuck extends Duck implements Inotator {
    public SwimmingDuck(long id, String username, String email, String password, double viteza, double rezistenta) {
        super(id, username, email, password, viteza, rezistenta);
    }

    @Override
    public void inoata() {
    }
}
