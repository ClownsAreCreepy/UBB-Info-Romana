package scs.domain.user;

import scs.domain.behaviors.Flying;

public class FlyingDuck extends Duck implements Flying {
    public FlyingDuck(Long id, String username, String email, String password, double speed, double resistance) {
        super(id, username, email, password, speed, resistance);
    }

    @Override
    public void fly() {
    }
}