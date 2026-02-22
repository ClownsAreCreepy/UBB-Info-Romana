package domain.event;

import domain.user.User;

import java.time.Instant;
import java.util.*;

public class Event {
    private final long id;
    private String name;
    private final Set<Long> subscriberIds = new HashSet<>();
    private Instant lastNotifiedAt;
    private String lastNotification;

    public Event(long id, String name) {
        this.id = id;
        this.name = name;
    }


    public long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Set<Long> getSubscribers() {
        return Collections.unmodifiableSet(subscriberIds);
    }

    public Instant getLastNotifiedAt() {
        return lastNotifiedAt;
    }

    public String getLastNotification() {
        return lastNotification;
    }


    public boolean subscribe(User u) {
        return subscriberIds.add(u.getId());
    }

    public boolean unsubscribe(User u) {
        return subscriberIds.remove(u.getId());
    }

    public void notifySubscribers(String message) {
        this.lastNotification = message;
        this.lastNotifiedAt = Instant.now();
    }

    @Override
    public String toString() {
        return "Event{id=" + id + ", name='" + name + "', subscribers=" + subscriberIds.size() + '}';
    }
}
