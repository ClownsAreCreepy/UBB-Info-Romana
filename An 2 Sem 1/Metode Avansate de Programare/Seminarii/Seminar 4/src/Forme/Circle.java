package Forme;

public class Circle {
    final double r;

    public Circle(double r) {
        this.r = r;
    }

    public String toString() {
        return "Circle(" + r + ")";
    }

    public double getR(){
        return r;
    }
}
