package curs.practic.Util.observer;
import curs.practic.Util.event.Event;

public interface Observer<E extends Event> {
    void update(E e);
}