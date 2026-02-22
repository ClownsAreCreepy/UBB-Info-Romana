package scs.service;

import scs.domain.user.Duck;
import scs.domain.event.Event;
import scs.domain.event.RaceEvent;
import scs.domain.user.User;
import scs.repo.events.EventRepository;
import scs.repo.users.UserRepository;
import scs.service.social.MessageService;
import scs.service.social.UserService;
import scs.utilities.errors.NotFoundException;
import scs.utilities.events.ChangeEventType;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observable;
import scs.utilities.paging.Pageable;
import scs.utilities.validator.NotBlankValidator;
import scs.utilities.validator.Validators;

import java.util.ArrayList;
import java.util.List;


public class EventService extends Observable<EntityChangeEvent<Event>> {
    private final EventRepository repo;
    private final UserRepository users;
    private final MessageService messages;

    public EventService(EventRepository repo, UserRepository users, MessageService messages) {
        this.repo = repo;
        this.users = users;
        this.messages = messages;
    }

    public Event createEvent(String name) {
        new NotBlankValidator("event name").validate(name);
        Validators.maxLength("event name", 50).validate(name);

        Event e = new Event(null, name);
        repo.add(e);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADD,e ));

        return e;
    }

    public void renameEvent(Long id, String newName) {
        new NotBlankValidator("event name").validate(newName);
        Validators.maxLength("event name", 50).validate(newName);

        Event e = repo.findById(id);
        e.setName(newName);
        repo.update(e);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE,e ));
    }

    public void deleteEvent(Long id) {
        Event e = new Event(id, "Deleted Event");
        repo.delete(id);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.DELETE, e));
    }

    public Event findById(Long id) {
        return repo.findById(id);
    }

    public List<Event> getAll() {
        return repo.getAll();
    }

    public void subscribe(Long eventId, Long userId) {
        // ensure user exists
        if (!users.existsById(userId))
            throw new NotFoundException("not found", "User " + userId + " does not exist");

        repo.addSubscriber(eventId, userId);

        Event updated = repo.findById(eventId);
        notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE, updated));
    }

    public void unsubscribe(Long eventId, Long userId) {
        repo.removeSubscriber(eventId, userId);

        Event updated = repo.findById(eventId);

        if (updated.getSubscribers().isEmpty()) {
            deleteEvent(updated.getId());

        } else
            notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE, updated));
    }

    public RaceEvent.Result runRaceInMemory(String raceName, List<Long> candidateIds, double[] lanes) {
        List<User> fetched = users.search(
                new Pageable(0, candidateIds.size()),
                "DUCK", "ALL",
                candidateIds,
                null
        ).getElementsOnPage();

        List<Duck> candidates = fetched.stream()
                .map(u -> (Duck) u)
                .toList();

        RaceEvent race = new RaceEvent(null, raceName, candidates, lanes, lanes.length);

        return race.runRace();
    }

    public void notifySubscribers(Long eventId, String messageText) {
        Event event = repo.findById(eventId);
        if (event == null)
            throw new NotFoundException("event", "Event " + eventId + " not found.");

        List<Long> subscriberIds = new ArrayList<>(event.getSubscribers());
        if (subscriberIds.isEmpty())
            return;

        messages.sendMessage(UserService.RACE_BOT_ID, subscriberIds, messageText, null);
    }
}
