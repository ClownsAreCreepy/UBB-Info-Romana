package scs.utilities.observer;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public abstract class Observable<E> {
    private final List<Observer<E>> observers = new CopyOnWriteArrayList<>();

    public void addObserver(Observer<E> o) { observers.add(o); }
    public void removeObserver(Observer<E> o) { observers.remove(o); }
    protected void notifyObservers(E event) { observers.forEach(o -> o.update(event)); }
}