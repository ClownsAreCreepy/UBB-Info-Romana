package scs.service;

import scs.domain.group.Herd;
import scs.domain.group.Performance;
import scs.domain.user.Duck;
import scs.repo.herds.HerdRepository;
import scs.utilities.events.ChangeEventType;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observable;
import scs.utilities.validator.NotBlankValidator;
import scs.utilities.validator.Validators;

import java.util.List;

public class HerdService extends Observable<EntityChangeEvent<Herd<Duck>>> {
    private final HerdRepository<Duck> repo;

    public HerdService(HerdRepository<Duck> repo) {
        this.repo = repo;
    }

    public Herd<Duck> createHerd(String name) {
        new NotBlankValidator("name").validate(name);
        Validators.maxLength("name", 30).validate(name);

        Herd<Duck> h = new Herd<>(name);
        repo.add(h);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADD, h));
        return h;
    }

    public void deleteHerd(Long id) {
        Herd<Duck> deleted = new Herd<>(id, "Deleted");
        repo.deleteById(id);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.DELETE, deleted));
    }

    public List<Herd<Duck>> getAll() {
        return repo.getAll();
    }

    public Herd<Duck> findById(Long id) {
        return repo.findById(id);
    }

    public void addDuck(Long herdId, Duck duck) {
        repo.addDuck(herdId, duck.getId());

        Herd<Duck> updated = repo.findById(herdId);
        notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE, updated));
    }

    public void deleteDuck(Long herdId, Long duckId) {
        repo.removeDuck(herdId, duckId);

        Herd<Duck> updated = repo.findById(herdId);

        if (updated.getMembers().isEmpty())
            deleteHerd(herdId);
        else
            notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE, updated));
    }

    public Performance performance(Long herdId) {
        Herd<Duck> h = findById(herdId);
        return h.getAvgPerformance();
    }

    public List<Duck> members(Long herdId) {
        return repo.findById(herdId).getMembers();
    }
}
