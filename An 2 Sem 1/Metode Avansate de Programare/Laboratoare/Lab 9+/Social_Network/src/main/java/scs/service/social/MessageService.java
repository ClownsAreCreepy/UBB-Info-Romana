package scs.service.social;

import scs.domain.interactions.Message;
import scs.domain.user.User;
import scs.repo.messages.MessageRepository;
import scs.repo.users.UserRepository;
import scs.utilities.errors.NotFoundException;
import scs.utilities.errors.ValidationException;
import scs.utilities.events.ChangeEventType;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observable;
import scs.utilities.paging.Pageable;

import java.util.List;

public class MessageService extends Observable<EntityChangeEvent<Message>> {


    private final MessageRepository repo;
    private final UserRepository userRepo;

    public MessageService(MessageRepository repo, UserRepository userRepo) {
        this.repo = repo;
        this.userRepo = userRepo;
    }

    public void sendMessage(Long senderId, List<Long> targetIds, String text, Long replyToId) {
        // Validation
        if (text == null || text.trim().isEmpty())
            throw new ValidationException("message", "Message text cannot be empty.");

        if (targetIds == null || targetIds.isEmpty())
            throw new ValidationException("recipients", "You must select at least one recipient.");

        // Load Sender
        User sender = userRepo.findById(senderId);
        if (sender == null)
            throw new NotFoundException("sender", "Sender not found.");

        // Load recipients
        List<User> recipients = userRepo.search(
                new Pageable(0, targetIds.size()),
                "ALL", "ALL",
                targetIds,
                null
        ).getElementsOnPage();

        if (recipients.isEmpty())
            throw new ValidationException("recipients", "The recipient/s don't exist.");

        // Load reply
        Message replyMsg = null;
        if (replyToId != null) {
            replyMsg = repo.findById(replyToId);
            if (replyMsg == null)
                throw new NotFoundException("reply", "The message you are replying to no longer exists.");
        }

        // Create
        Message msg = new Message(sender, recipients, text, replyMsg);
        repo.save(msg);

        EntityChangeEvent<Message> event = new EntityChangeEvent<>(ChangeEventType.ADD, msg);
        notifyObservers(event);
    }

    public List<Message> getConversation(Long id1, Long id2) {
        if (!userRepo.existsById(id1)) throw new NotFoundException("user", "User with id" + id1 + " does not exist.");
        if (!userRepo.existsById(id2)) throw new NotFoundException("user", "User with id" + id2 + " does not exist.");

        return repo.findConversation(id1, id2);
    }
}
