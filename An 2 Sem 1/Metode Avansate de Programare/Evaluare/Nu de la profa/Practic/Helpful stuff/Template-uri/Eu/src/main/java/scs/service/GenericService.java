package scs.service;

import scs.utilities.events.*;
import scs.utilities.observer.Observable;
import scs.repo.Repository;
import javafx.application.Platform;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.TimeUnit;

public class GenericService<E> extends Observable<EntityChangeEvent<E>> {

    protected final Repository<E> repo;

    public GenericService(Repository<E> repo) {
        this.repo = repo;
    }

    public List<E> getAll() {
        return repo.findAll();
    }

    public E add(E entity) {
        E saved = repo.save(entity);
        notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADD, saved));
        return saved;
    }

    public void update(E entity) {
        repo.update(entity);
        notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE, entity));
    }

    public void delete(Long id) {
        // try to find it first so we can notify the UI which object was deleted
        E old = repo.findOne(id).orElse(null);
        repo.delete(id);
        if (old != null) {
            notifyObservers(new EntityChangeEvent<>(ChangeEventType.DELETE, old));
        }
    }

    public void processAsync(E entity, Runnable action) {
        CompletableFuture.delayedExecutor(5, TimeUnit.SECONDS).execute(() -> {
            try {
                // run logic
                action.run();

                // notify UI
                Platform.runLater(() -> {
                    // force refresh or specific update
                    notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE, entity));
                });
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }
}