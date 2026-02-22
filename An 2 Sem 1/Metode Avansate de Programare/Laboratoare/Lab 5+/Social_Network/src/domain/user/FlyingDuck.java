package domain.user;

import domain.behaviors.Zburator;

public class FlyingDuck extends Duck implements Zburator {
    public FlyingDuck(long id, String username, String email, String password, double viteza, double rezistenta) {
        super(id, username, email, password, viteza, rezistenta);
    }

    @Override
    public void zboara() {
    }
}