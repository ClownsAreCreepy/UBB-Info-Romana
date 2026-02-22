package service;

import domain.event.Event;
import repo.events.EventRepository;
import repo.users.UserRepository;
import utilities.IdGenerator;
import utilities.errors.NotFoundException;
import utilities.validator.NotBlankValidator;

import java.util.List;

public class EventService {
    private final EventRepository repo;
    private final UserRepository users;
    private final IdGenerator ids;

    public EventService(EventRepository repo, UserRepository users, IdGenerator ids) {
        this.repo = repo;
        this.users = users;
        this.ids = ids;
    }

    // --------- EVENTS ---------
    public Event createEvent(String name) {
        new NotBlankValidator("event name").validate(name);

        long id = ids.next();
        Event e = new Event(id, name);

        repo.add(e);
        return e;
    }

    public void renameEvent(long id, String newName) {
        new NotBlankValidator("event name").validate(newName);

        Event e = repo.findById(id);
        e.setName(newName);
        repo.update(e);
    }

    public void deleteEvent(long id) {
        repo.delete(id);
    }

    public Event findById(long id) {
        return repo.findById(id);
    }

    public List<Event> getAll() {
        return repo.getAll();
    }

    // --------- SUBSCRIBERS ---------
    public void subscribe(long eventId, long userId) {
        // ensure user exists
        users.findById(userId);
        repo.addSubscriber(eventId, userId);
    }

    public void unsubscribe(long eventId, long userId) {
        repo.removeSubscriber(eventId, userId);
    }

    // --------- NOTIFICATION LOGIC ---------
    public void notifySubscribers(long eventId, String message) {
        new NotBlankValidator("notification").validate(message);

        Event e = repo.findById(eventId);
        e.notifySubscribers(message); // sets fields in the domain object
        repo.update(e);
    }
}
