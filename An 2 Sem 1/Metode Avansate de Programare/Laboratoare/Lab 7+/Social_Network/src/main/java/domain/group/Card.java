package domain.group;

import domain.user.Duck;

import java.util.*;

public class Card<T extends Duck> {
    private long id;
    private String numeCard;
    private final List<T> members = new ArrayList<>();
    private final Map<Long, T> ids = new HashMap<>();

    public Card(long id, String numeCard) {
        this.id = id;
        setNumeCard(numeCard);
    }

    public Card(String numeCard) {
        this.numeCard = numeCard;
    }


    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getNumeCard() {
        return numeCard;
    }

    public void setNumeCard(String numeCard) {
        this.numeCard = Objects.requireNonNull(numeCard).trim();
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
        return members.removeIf(m -> m.getId() == duck.getId());
    }

    public boolean removeDuckById(Long id) {
        ids.remove(id);
        return members.removeIf(m -> m.getId() == id);
    }

    public Optional<T> findDuckById(Long id) {
        return Optional.ofNullable(ids.get(id));
    }

    public Performance getAvgPerformance() {
        if (members.isEmpty())
            return Performance.ZERO;

        double sumV = 0.0, sumR = 0.0;

        for (T m : members) {
            sumV += m.getViteza();
            sumR += m.getRezistenta();
        }

        double n = members.size();
        return new Performance(sumV / n, sumR / n);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Card<?> card))
            return false;

        return id == card.id;
    }

    @Override
    public int hashCode() {
        return Long.hashCode(id);
    }

    @Override
    public String toString() {
        return "Card{id=" + id + ", numeCard='" + numeCard + "', members=" + members.size() + "}";
    }

}
