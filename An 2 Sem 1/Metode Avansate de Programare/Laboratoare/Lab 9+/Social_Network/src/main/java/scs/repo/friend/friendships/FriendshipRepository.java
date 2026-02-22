package scs.repo.friend.friendships;

import java.util.List;
import java.util.Set;

public interface FriendshipRepository {
    void addUser(Long id);
    void removeUser(Long id);

    void addFriendship(Long id1, Long id2);
    void removeFriendship(Long id1, Long id2);

    Set<Long> getFriends(Long id);
    Set<Long> getAllUsers();
    boolean areFriends(Long id1, Long id2);
    int nrFriends(Long id1);

    List<Long[]> findAllEdges();
}
