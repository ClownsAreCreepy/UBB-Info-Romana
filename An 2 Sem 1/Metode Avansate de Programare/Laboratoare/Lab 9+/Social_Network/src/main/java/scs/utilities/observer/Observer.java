package scs.utilities.observer;

@FunctionalInterface
public interface Observer<E> {
    void update(E event);
}
