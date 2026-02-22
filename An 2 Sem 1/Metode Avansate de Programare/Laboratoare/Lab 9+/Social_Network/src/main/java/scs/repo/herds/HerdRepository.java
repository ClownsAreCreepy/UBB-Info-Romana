package scs.repo.herds;

import scs.domain.group.Herd;
import scs.domain.user.Duck;

import java.util.List;

public interface HerdRepository<T extends Duck> {
    void add(Herd<T> herd);
    void addDuck(Long cardId, Long duckId);

    void update(Herd<T> herd);

    Herd<T> findById(Long id);
    Herd<T> findByName(String name);

    List<Herd<T>> getAll();

    void deleteById(Long id);
    void removeDuck(Long cardId, Long duckId);

    boolean existsById(Long id);
    boolean existsByName(String name);
}
