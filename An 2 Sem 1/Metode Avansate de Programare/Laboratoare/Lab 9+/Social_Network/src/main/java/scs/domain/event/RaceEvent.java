package scs.domain.event;

import scs.domain.behaviors.Swimming;
import scs.domain.user.Duck;
import scs.utilities.errors.NotFoundException;

import java.util.*;
import java.util.stream.Collectors;

public class RaceEvent extends Event {
    public record LaneResult(Long duckId, int lane, double distance, double velocity, double time) {
    }

    public record Result(List<LaneResult> lanes, double totalTime) {
    }

    private final List<Duck> candidates;
    private final double[] lanes;      // distances d1 .. dLaneCount
    private final int laneCount;       // lane number

    public RaceEvent(Long id, String name, List<Duck> candidates, double[] lanes, int m) {
        super(id, name);
        this.candidates = new ArrayList<>(candidates);
        this.lanes = Arrays.copyOf(lanes, lanes.length);
        this.laneCount = m;
    }

    public static boolean canSwim(Duck d) {
        return d instanceof Swimming;
    }

    public Result runRace() {
        List<Duck> swimmers = candidates.stream()
                .filter(RaceEvent::canSwim)
                .collect(Collectors.toList());

        if (swimmers.size() < laneCount)
            throw new NotFoundException("no ducks", "Not enough ducks for these many lanes.");

        swimmers.sort(Comparator.comparingDouble(Duck::getResistance).reversed());

        List<Duck> chosen = new ArrayList<>(swimmers.subList(0, laneCount));

        List<LaneResult> laneResults = new ArrayList<>();
        double maxTime = 0.0;

        for (int i = 0; i < laneCount; ++i) {
            Duck duck = chosen.get(i);
            int lane = i + 1;
            double d = lanes[i];
            double v = duck.getSpeed();
            double t = (2.0 * d) / v;

            maxTime = Math.max(maxTime, t);

            laneResults.add(new LaneResult(duck.getId(), lane, d, v, t));
        }

        return new Result(Collections.unmodifiableList(laneResults), maxTime);
    }
}
