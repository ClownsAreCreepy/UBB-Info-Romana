package scs.repo.messages;

import scs.domain.interactions.Message;

import java.util.List;

public interface MessageRepository {
    void save(Message m);

    Message findById(Long id);
    List<Message> findConversation(Long u1, Long u2);
}
