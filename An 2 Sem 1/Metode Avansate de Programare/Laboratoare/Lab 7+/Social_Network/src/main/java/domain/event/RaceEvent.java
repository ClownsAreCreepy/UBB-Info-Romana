package domain.event;

import domain.behaviors.Inotator;
import domain.user.Duck;
import utilities.errors.NotFoundException;

import java.util.*;

public class RaceEvent extends Event {
    public record LaneResult(long duckId, int lane, double distance, double velocity, double time) {
    }

    public record Result(List<LaneResult> lanes, double totalTime) {
    }

    private final List<Duck> candidates;
    private final double[] balize;      // distantele d1 .. dM
    private final int M;                // nr de culor

    public RaceEvent(long id, String name, List<Duck> candidates, double[] balize, int m) {
        super(id, name);
        this.candidates = new ArrayList<>(candidates);
        this.balize = Arrays.copyOf(balize, balize.length);
        this.M = m;
    }

    private boolean canSwim(Duck d) {
        return d instanceof Inotator;
    }

    public Result runRace() {
        List<Duck> swimmers = new ArrayList<>(candidates.stream()
                .filter(this::canSwim)
                .toList());

        if (swimmers.size() < M)
            throw new NotFoundException("no ducks", "Not enough ducks for these many lanes.");

        swimmers.sort(Comparator.comparingDouble(Duck::getRezistenta).reversed());

        List<Duck> chosen = new ArrayList<>(swimmers.subList(0, M));

        List<LaneResult> lines = new ArrayList<>();
        double maxTime = 0.0;

        for (int i = 0; i < M; ++i) {
            Duck duck = chosen.get(i);
            int lane = i + 1;
            double d = balize[i];
            double v = duck.getViteza();
            double t = (2.0 * d) / v;

            maxTime = Math.max(maxTime, t);

            lines.add(new LaneResult(duck.getId(), lane, d, v, t));
        }

        return new Result(Collections.unmodifiableList(lines), maxTime);
    }
}
