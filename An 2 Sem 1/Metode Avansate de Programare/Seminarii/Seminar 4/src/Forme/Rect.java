package Forme;

public class Rect {
    final double w, h;

    public Rect(double w, double h) {
        this.w = w;
        this.h = h;
    }

    public String toString() {
        return "Rect(" + w + "x" + h + ")";
    }

    public double getW() {
        return w;
    }

    public double getH() {
        return h;
    }
}
