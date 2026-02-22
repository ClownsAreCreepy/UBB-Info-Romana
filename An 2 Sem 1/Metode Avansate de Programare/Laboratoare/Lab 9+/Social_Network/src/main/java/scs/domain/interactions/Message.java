package scs.domain.interactions;


import scs.domain.user.User;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Message {
    private Long id;
    private User from;
    private List<User> to;
    private String text;
    private LocalDateTime date;
    private Message reply;

    // Constructor for loading from DB
    public Message(Long id, User from, List<User> to, String text, LocalDateTime date, Message reply) {
        this.id = id;
        this.from = from;
        this.to = to != null ? new ArrayList<>(to) : new ArrayList<>();
        this.text = text;
        this.date = date;
        this.reply = reply;
    }

    // Constructor for new message
    public Message(User from, List<User> to, String text) {
        this(null, from, to, text, LocalDateTime.now(), null);
    }

    // Constructor for reply message
    public Message(User from, List<User> to, String text, Message reply) {
        this(null, from, to, text, LocalDateTime.now(), reply);
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

    public List<User> getTo() {
        return to;
    }

    public String getText() {
        return text;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public Message getReply() {
        return reply;
    }

    public void setReply(Message reply) {
        this.reply = reply;
    }

    @Override
    public String toString() {
        String replyStrId = (reply == null) ? "null" : String.valueOf(reply.getId());
//        String replyStrText = (reply == null) ? "null" : reply.getText();
        return "Message{id=" + id + ", from=" + from.getUsername() + ", text = '" + text + "', replyTo=" + replyStrId + "}";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Message message)) return false;
        return Objects.equals(id, message.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}
