package Domain;

public class Result {
    private double bestTime;    // minimal race duration
    private int[] laneDuck;     // lane j (0-based) -> duckID (1-based)

    public Result(int m){
        laneDuck = new int[m];
        for (int i = 0; i < m; ++i)
            laneDuck[i] = -1;
    }


    public double getBestTime() {
        return bestTime;
    }

    public void setBestTime(double new_bestTime) {
        this.bestTime = new_bestTime;
    }


    public int[] getLaneDuck() {
        return laneDuck;
    }

    public void setLaneDuck(int lane, int duckID) {
        laneDuck[lane] = duckID;
    }
}
