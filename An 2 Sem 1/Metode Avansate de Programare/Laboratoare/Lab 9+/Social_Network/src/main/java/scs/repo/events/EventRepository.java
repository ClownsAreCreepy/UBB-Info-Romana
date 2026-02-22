package scs.repo.events;

import scs.domain.event.Event;

import java.util.List;

public interface EventRepository {

    // CRUD
    void add(Event event);
    void update(Event event);
    void delete(Long id);

    Event findById(Long id);
    List<Event> getAll();

    // Subscribers
    void addSubscriber(Long eventId, Long userId);
    void removeSubscriber(Long eventId, Long userId);
}
