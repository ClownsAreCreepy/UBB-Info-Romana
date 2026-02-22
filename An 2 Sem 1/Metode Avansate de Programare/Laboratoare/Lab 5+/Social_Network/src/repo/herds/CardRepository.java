package repo.herds;

import domain.group.Card;
import domain.user.Duck;

import java.util.List;
import java.util.Optional;

public interface CardRepository<T extends Duck> {
    void add(Card<T> card);

    void update(Card<T> card);

    Card<T> findById(long id);
    Card<T> findByName(String name);

    List<Card<T>> getAll();

    void deleteById(long id);

    boolean existsById(long id);
    boolean existsByName(String name);
}
