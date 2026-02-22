package repo.friendships;

import java.util.List;
import java.util.Set;

public interface FriendshipRepository {
    void addUser(long id);
    void removeUser(long id);

    void addFriendship(long id1, long id2);
    void removeFriendship(long id1, long id2);

    Set<Long> getFriends(long id);
    Set<Long> getAllUsers();
    boolean areFriends(long id1, long id2);
    int nrFriends(long id1);

    List<long[]> findAllEdges();
}
