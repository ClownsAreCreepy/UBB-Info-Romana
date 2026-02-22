package scs.repo.friend.requests;

import scs.domain.interactions.FriendRequest;

import java.util.List;

public interface RequestRepository {
    void save(FriendRequest request);
    void update(FriendRequest request);
    void delete(FriendRequest request);

    FriendRequest findOne(Long fromId, Long toId);

    List<FriendRequest> findPending(Long toUserId);
}
