package scs.domain.group;

import scs.domain.user.Duck;

import java.util.*;

public class Herd<T extends Duck> {
    private Long id;
    private String name;
    private final List<T> members = new ArrayList<>();
    private final Map<Long, T> ids = new HashMap<>();

    public Herd(Long id, String name) {
        this.id = id;
        this.name = name;
    }

    public Herd(String name) {
        this.name = name;
    }


    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = Objects.requireNonNull(name).trim();
    }

    public List<T> getMembers() {
        return Collections.unmodifiableList(members);
    }

    public int size() {
        return members.size();
    }

    public void addDuck(T duck) {
        ids.put(duck.getId(), duck);
        members.add(duck);
    }

    public boolean removeDuck(T duck) {
        ids.remove(duck.getId());
        return members.removeIf(m -> Objects.equals(m.getId(), duck.getId()));
    }

    public boolean removeDuckById(Long id) {
        ids.remove(id);
        return members.removeIf(m -> Objects.equals(m.getId(), id));
    }

    public Optional<T> findDuckById(Long id) {
        return Optional.ofNullable(ids.get(id));
    }

    public Performance getAvgPerformance() {
        if (members.isEmpty())
            return Performance.ZERO;

        double sumV = 0.0, sumR = 0.0;

        for (T m : members) {
            sumV += m.getSpeed();
            sumR += m.getResistance();
        }

        double n = members.size();
        return new Performance(sumV / n, sumR / n);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Herd<?> herd))
            return false;

        return Objects.equals(id, herd.id);
    }

    @Override
    public int hashCode() {
        return Long.hashCode(id);
    }

    @Override
    public String toString() {
        return "Herd{id=" + id + ", name='" + name + "', members=" + members.size() + "}";
    }

}
