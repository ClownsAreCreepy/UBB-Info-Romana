package Service;

import Domain.*;
import Domain.Result;

public class CrazyDuck extends Task {
    private ProblemData date;

    public CrazyDuck(ProblemData data) {
        this.date = data;
    }

    public ProblemData getDate() {
        return date;
    }

    // returns Result(with lane->duck assignment) if feasible in time T
    private Result checkPosibil(double T) {
        int N = date.getN(), M = date.getM();
        Duck[] ducks = date.getDucks();
        double[] d = date.getBalizeAsDouble();

        double[] needV = new double[M];
        for (int j = 0; j < M; j++)
            needV[j] = (2.0 * d[j]) / T;

        Duck[] byStam = TaskSort.byStaminaDesc(ducks);
        boolean[] used = new boolean[N];
        int prevR = Integer.MAX_VALUE;

        Result res = new Result(M);

        for (int lane = 0; lane < M; lane++) {
            double req = needV[lane];
            int pickIdx = -1;

            for (int k = 0; k < byStam.length; k++) {
                Duck cand = byStam[k];
                if (used[cand.getId() - 1]) continue;
                if (cand.getResistance() > prevR) continue;     // keep non-increasing
                if (cand.getSpeed() + 1e-12 < req) continue;    // needs enough speed
                pickIdx = k;                                    // first fit (max r due to sort)
                break;
            }

            if (pickIdx == -1) return null; // not feasible
            Duck pick = byStam[pickIdx];
            used[pick.getId() - 1] = true;
            res.setLaneDuck(lane, pick.getId());
            prevR = pick.getResistance();
        }
        return res;
    }

    @Override
    public void execute() {
        // binary search minimal feasible time
        int M = date.getM();
        double lo = 0.0;
        double hi = TaskConfig.getMaxTime(date);
        Result best = new Result(M);

        for (int i = 0; i < 60; ++i) {
            double mid = (lo + hi) / 2;
            Result r = checkPosibil(mid);
            if (r != null) {
                // feasible: keep it
                hi = mid;
                best = r;
            } else {
                lo = mid;
            }
        }

        best.setBestTime(hi);
        date.setResult(best);

        // fill DucksWhoMadeIt(chosen)
        Duck[] chosen = new Duck[M];
        for (int lane = 0; lane < M; ++lane) {
            int id = best.getLaneDuck()[lane];
            chosen[lane] = date.getDucks()[id - 1];
        }
        date.setDucksWhoMadeIt(chosen);
    }

}
