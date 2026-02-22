package scs.domain.event;

import scs.domain.group.Herd;
import scs.domain.user.User;

import java.util.Collections;
import java.util.Objects;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

public class Event {
    private Long id;
    private String name;
    private final Set<Long> subscriberIds = ConcurrentHashMap.newKeySet();

    public Event(Long id, String name) {
        this.id = id;
        this.name = name;
    }


    public Long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Set<Long> getSubscribers() {
        return Collections.unmodifiableSet(subscriberIds);
    }


    public boolean subscribe(User u) {
        return subscriberIds.add(u.getId());
    }

    public boolean subscribeById(Long id) {
        return subscriberIds.add(id);
    }

    public boolean unsubscribe(User u) {
        return subscriberIds.remove(u.getId());
    }

    public boolean unsubscribeById(Long id) {
        return subscriberIds.remove(id);
    }

    public void notifySubscribers(String message) {
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;

        if (!(o instanceof Herd<?> herd))
            return false;

        return Objects.equals(id, herd.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(id);
    }

    @Override
    public String toString() {
        return "Event{id=" + id + ", name='" + name + "', subscribers=" + subscriberIds.size() + '}';
    }
}
