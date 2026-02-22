package Service;

import Domain.*;

import java.util.Arrays;

public class TaskConfig {
    // upper bound for binary search: slowest duck across longest lane (dus intors)
    public static double getMaxTime(ProblemData data){
        double[] d = data.getBalizeAsDouble();
        Duck[] ducks = data.getDucks();
        double maxD = d[d.length - 1];
        double minV = Arrays.stream(ducks).mapToDouble(Duck::getSpeed).min().orElse(1.0);
        return 2.0 * maxD / minV;
    }
}
