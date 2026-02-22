package repo.herds;

import domain.group.Card;
import domain.user.Duck;

import java.util.List;

public interface CardRepository<T extends Duck> {
    void add(Card<T> card);
    void addDuck(long cardId, long duckId);

    void update(Card<T> card);

    Card<T> findById(long id);
    Card<T> findByName(String name);

    List<Card<T>> getAll();

    void deleteById(long id);
    void removeDuck(long cardId, long duckId);

    boolean existsById(long id);
    boolean existsByName(String name);
}
