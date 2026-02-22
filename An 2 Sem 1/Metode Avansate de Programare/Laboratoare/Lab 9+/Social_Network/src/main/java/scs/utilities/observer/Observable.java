package scs.utilities.observer;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public abstract class Observable<E> {
    private final List<Observer<E>> observers = new CopyOnWriteArrayList<>();

    public void addObserver(Observer<E> observer) {
        observers.add(observer);
    }

    public void removeObserver(Observer<E> observer) {
        observers.remove(observer);
    }

    protected void notifyObservers(E event) {
        for (Observer<E> obs : observers)
            obs.update(event);
    }

}
