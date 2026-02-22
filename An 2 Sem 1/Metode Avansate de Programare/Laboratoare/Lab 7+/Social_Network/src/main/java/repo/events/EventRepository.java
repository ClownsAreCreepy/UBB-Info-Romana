package repo.events;

import domain.event.Event;

import java.util.List;

public interface EventRepository {

    // CRUD
    void add(Event event);
    void update(Event event);
    void delete(long id);

    Event findById(long id);
    List<Event> getAll();

    // Subscribers
    void addSubscriber(long eventId, long userId);
    void removeSubscriber(long eventId, long userId);
}
