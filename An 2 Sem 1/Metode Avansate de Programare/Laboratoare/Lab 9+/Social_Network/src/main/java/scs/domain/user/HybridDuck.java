package scs.domain.user;

import scs.domain.behaviors.Swimming;
import scs.domain.behaviors.Flying;

public class HybridDuck extends Duck implements Swimming, Flying {
    public HybridDuck(Long id, String username, String email, String password, double speed, double resistance) {
        super(id, username, email, password, speed, resistance);
    }

    @Override
    public void fly() {
    }

    @Override
    public void swim() {
    }
}