package curs.practic.Service;

import curs.practic.Util.event.EntityChangeEvent;
import curs.practic.Util.observer.Observable;
import curs.practic.Util.observer.Observer;

import java.util.ArrayList;
import java.util.List;

public class Service implements Observable<EntityChangeEvent<?>> {

    private final List<Observer<EntityChangeEvent<?>>> observers = new ArrayList<>();

    @Override
    public void addObserver(Observer<EntityChangeEvent<?>> o) {
        observers.add(o);
    }

    @Override
    public void removeObserver(Observer<EntityChangeEvent<?>> o) {
        observers.remove(o);
    }

    @Override
    public void notifyObservers(EntityChangeEvent<?> e) {
        observers.forEach(o -> o.update(e));
    }




}
