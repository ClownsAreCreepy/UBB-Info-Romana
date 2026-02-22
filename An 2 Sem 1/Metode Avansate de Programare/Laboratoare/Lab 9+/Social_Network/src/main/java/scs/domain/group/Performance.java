package scs.domain.group;

/**
 * Represents the average performance of herd
 *
 * @param avgSpeed      - average speed of members
 * @param avgResistance - average resistance of members
 */
public record Performance(double avgSpeed, double avgResistance) {
    public static final Performance ZERO = new Performance(0.0, 0.0);
}