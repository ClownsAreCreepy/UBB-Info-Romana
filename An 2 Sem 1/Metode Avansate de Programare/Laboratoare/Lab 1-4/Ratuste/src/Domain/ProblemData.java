package Domain;

import java.util.Arrays;

public class ProblemData {
    private int n;
    private int m;
    private int[] balize;           // distances
    private Duck[] ducks;
    private Result result;
    private Duck[] DucksWhoMadeIt;  // chosen ducks in order of lanes


    public int getN() {
        return n;
    }

    public int getM() {
        return m;
    }

    public int[] getBalize() {
        return balize;
    }

    public Duck[] getDucks() {
        return ducks;
    }

    public Result getResult() {
        return result;
    }

    public Duck[] getDucksWhoMadeIt() {
        return DucksWhoMadeIt;
    }

    public void setN(int new_n) {
        this.n = new_n;
    }

    public void setM(int new_m) {
        this.m = new_m;
    }

    public void setBalize(int[] new_balize) {
        this.balize = new_balize;
    }

    public void setDucks(Duck[] new_ducks) {
        this.ducks = new_ducks;
    }

    public void setResult(Result new_result) {
        this.result = new_result;
    }

    public void setDucksWhoMadeIt(Duck[] new_ducksWhoMadeIt) {
        DucksWhoMadeIt = new_ducksWhoMadeIt;
    }

    public double[] getBalizeAsDouble() {
        double[] d = new double[balize.length];
        for (int i = 0; i < balize.length; ++i)
            d[i] = balize[i];
        return d;
    }

    @Override
    public String toString() {
        return "ProblemData{" +
                "n=" + n +
                ", m=" + m +
                ", balize=" + Arrays.toString(balize) +
                ", ducks=" + Arrays.toString(ducks) +
                ", result=" + result +
                ", DucksWhoMadeIt=" + Arrays.toString(DucksWhoMadeIt) +
                '}';
    }
}
