package scs.service.friend;

import scs.domain.interactions.FriendRequest;
import scs.domain.interactions.RequestStatus;
import scs.domain.user.User;
import scs.repo.friend.requests.RequestRepository;
import scs.repo.users.UserRepository;
import scs.utilities.errors.NotFoundException;
import scs.utilities.errors.ValidationException;
import scs.utilities.events.ChangeEventType;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observable;

import java.util.List;

public class RequestService extends Observable<EntityChangeEvent<FriendRequest>> {
    private final RequestRepository requestRepo;
    private final FriendshipService friendshipService;
    private final UserRepository userRepo;

    public RequestService(RequestRepository requestRepo, FriendshipService friendshipService, UserRepository userRepo) {
        this.requestRepo = requestRepo;
        this.friendshipService = friendshipService;
        this.userRepo = userRepo;
    }

    public void sendRequest(Long fromId, Long toId) {
        if (fromId.equals(toId))
            throw new ValidationException("request", "Cannot send request to yourself.");

        User from = userRepo.findById(fromId);
        User to = userRepo.findById(toId);
        if (from == null || to == null)
            throw new NotFoundException("user", "User not found");

        if (friendshipService.areFriends(fromId, toId))
            throw new ValidationException("friendship", "You are already friends!");

        FriendRequest existing = requestRepo.findOne(fromId, toId);
        if (existing != null && existing.getStatus() == RequestStatus.PENDING)
            throw new ValidationException("request", "Request already pending.");

        FriendRequest reverse = requestRepo.findOne(toId, fromId);
        if (reverse != null && reverse.getStatus() == RequestStatus.PENDING)
            throw new ValidationException("request", "This user already sent you a friend request. Check your inbox.");

        FriendRequest req = new FriendRequest(from, to);
        requestRepo.save(req);

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADD, req));
    }

    public void acceptRequest(FriendRequest req) {
        if (req.getStatus() != RequestStatus.PENDING)
            throw new ValidationException("request", "Request is not pending.");

        requestRepo.delete(req);

        friendshipService.addFriendship(req.getFrom().getId(), req.getTo().getId());

        notifyObservers(new EntityChangeEvent<>(ChangeEventType.DELETE, req));
    }

    public void rejectRequest(FriendRequest req) {
        if (req.getStatus() != RequestStatus.PENDING)
            throw new ValidationException("request", "Request is not pending.");

        requestRepo.delete(req);
        notifyObservers(new EntityChangeEvent<>(ChangeEventType.DELETE, req));
    }

    public List<FriendRequest> getPendingRequests(Long userId) {
        return requestRepo.findPending(userId);
    }
}
