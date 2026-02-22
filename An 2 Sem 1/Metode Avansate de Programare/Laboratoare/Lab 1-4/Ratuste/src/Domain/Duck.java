package Domain;

public class Duck {
    private int id;
    private double speed;
    private int resistance;

    public Duck(int id, double speed, int resistance) {
        this.id = id;
        this.speed = speed;
        this.resistance = resistance;
    }

    public int getId() {
        return id;
    }

    public void setId(int new_id) {
        this.id = new_id;
    }

    public double getSpeed() {
        return speed;
    }

    public void setSpeed(double new_speed) {
        this.speed = new_speed;
    }

    public int getResistance() {
        return resistance;
    }

    public void setResistance(int new_resistance) {
        this.resistance = new_resistance;
    }

    @Override
    public String toString() {
        return "Data.Duck {id=" + id + ", v=" + speed + ", st=" + resistance + "}";
    }
}
