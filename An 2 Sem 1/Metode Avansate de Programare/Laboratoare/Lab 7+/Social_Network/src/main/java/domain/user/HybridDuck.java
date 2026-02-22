package domain.user;

import domain.behaviors.Inotator;
import domain.behaviors.Zburator;

public class HybridDuck extends Duck implements Inotator, Zburator {
    public HybridDuck(long id, String username, String email, String password, double viteza, double rezistenta) {
        super(id, username, email, password, viteza, rezistenta);
    }

    @Override
    public void inoata() {
    }

    @Override
    public void zboara() {
    }
}