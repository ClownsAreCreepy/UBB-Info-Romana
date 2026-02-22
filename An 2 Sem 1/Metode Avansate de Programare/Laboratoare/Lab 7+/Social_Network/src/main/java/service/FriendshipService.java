package service;

import domain.user.User;
import repo.friendships.FriendshipRepository;
import utilities.errors.NotFoundException;
import repo.users.UserRepository;
import utilities.errors.ValidationException;

import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class FriendshipService {
    private final UserRepository users;
    private final FriendshipRepository graph;

    public FriendshipService(UserRepository users, FriendshipRepository graph) {
        this.users = users;
        this.graph = graph;
    }

    public void addFriendship(long id1, long id2) {
        if (!users.existsById(id1) || !users.existsById(id2))
            throw new NotFoundException("user", "user(s) don't exist.");

        if (id1 == id2)
            throw new ValidationException("same ids","no self-friend!");

        graph.addFriendship(id1, id2);
    }

    public void removeFriendship(long id1, long id2) {
        graph.removeFriendship(id1, id2);
    }

    // when we add/remove users from repo, update graph
    public void syncWithUsers() {
        var existing = users.getAll().stream().map(User::getId).collect(Collectors.toSet());

        // add missing
        existing.forEach(graph::addUser);

        // remove ghosts
        for (long uid : graph.getAllUsers())
            if (!existing.contains(uid))
                graph.removeUser(uid);
    }

    public Set<Long> getFriendsOf(long id) {
        return graph.getFriends(id);
    }

    public List<User> getAllUsers() {
        return users.getAll();
    }
}
