package scs.service.friend;

import scs.domain.interactions.Friendship;
import scs.domain.user.User;
import scs.repo.friend.friendships.FriendshipRepository;
import scs.utilities.errors.NotFoundException;
import scs.repo.users.UserRepository;
import scs.utilities.errors.ValidationException;
import scs.utilities.events.ChangeEventType;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observable;

import java.util.List;
import java.util.Objects;
import java.util.Set;
import java.util.stream.Collectors;

public class FriendshipService extends Observable<EntityChangeEvent<Friendship>> {
    private final UserRepository users;
    private final FriendshipRepository graph;

    public FriendshipService(UserRepository users, FriendshipRepository graph) {
        this.users = users;
        this.graph = graph;
    }

    public void addFriendship(Long id1, Long id2) {
        if (!users.existsById(id1) || !users.existsById(id2))
            throw new NotFoundException("user", "user(s) don't exist.");

        if (Objects.equals(id1, id2))
            throw new ValidationException("same ids", "no self-friend!");

        graph.addFriendship(id1, id2);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADD, new Friendship(id1, id2)));
    }

    public void removeFriendship(Long id1, Long id2) {
        graph.removeFriendship(id1, id2);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.DELETE, new Friendship(id1, id2)));
    }

    // when we add/remove users from scs.repo, update graph
    public void syncWithUsers() {
        var existing = users.getAll().stream().map(User::getId).collect(Collectors.toSet());

        // add missing
        existing.forEach(graph::addUser);

        // remove ghosts
        for (Long uid : graph.getAllUsers())
            if (!existing.contains(uid))
                graph.removeUser(uid);
    }

    public Set<Long> getFriendsOf(Long id) {
        return graph.getFriends(id);
    }

    public boolean areFriends(Long id1, Long id2) {
        return graph.areFriends(id1, id2);
    }

    public List<User> getAllUsers() {
        return users.getAll();
    }
}
