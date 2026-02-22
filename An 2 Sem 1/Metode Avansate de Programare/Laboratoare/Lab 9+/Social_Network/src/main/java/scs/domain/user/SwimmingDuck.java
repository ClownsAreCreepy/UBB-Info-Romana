package scs.domain.user;

import scs.domain.behaviors.Swimming;

public class SwimmingDuck extends Duck implements Swimming {
    public SwimmingDuck(Long id, String username, String email, String password, double speed, double resistance) {
        super(id, username, email, password, speed, resistance);
    }

    @Override
    public void swim() {
    }

}
