package scs.domain.interactions;

import scs.domain.user.User;

import java.time.LocalDateTime;
import java.util.Objects;

public class FriendRequest {
    private Long id;
    private final User from;
    private final User to;
    private RequestStatus status;
    private final LocalDateTime date;

    // Constructor for loading from DB
    public FriendRequest(Long id, User from, User to, RequestStatus status, LocalDateTime date) {
        this.id = id;
        this.from = from;
        this.to = to;
        this.status = status;
        this.date = date;
    }

    // Constructor for creating a request
    public FriendRequest(User from, User to) {
        this(null, from, to, RequestStatus.PENDING, LocalDateTime.now());
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public User getFrom() {
        return from;
    }

    public User getTo() {
        return to;
    }

    public RequestStatus getStatus() {
        return status;
    }

    public void setStatus(RequestStatus status) {
        this.status = status;
    }

    public LocalDateTime getDate() {
        return date;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;

        if (!(obj instanceof FriendRequest that))
            return false;

        if (id != null && that.id != null)
            return Objects.equals(id, that.id);

        return Objects.equals(from, that.from) && Objects.equals(to, that.to);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public String toString() {
        return "FriendRequest{id=%d, from=%s, to=%s, status=%s}".formatted(
                id, from.getUsername(), to.getUsername(), status);
    }
}
