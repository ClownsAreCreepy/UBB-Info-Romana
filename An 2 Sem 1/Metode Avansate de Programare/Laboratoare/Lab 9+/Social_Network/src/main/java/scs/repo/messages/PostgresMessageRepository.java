package scs.repo.messages;

import scs.domain.interactions.Message;
import scs.domain.user.Person;
import scs.domain.user.User;
import scs.repo.users.PostgresUserRepository;
import scs.repo.users.UserRepository;
import scs.utilities.database.Db;
import scs.utilities.errors.DatabaseException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class PostgresMessageRepository implements MessageRepository {
    private final UserRepository userRepo;

    public PostgresMessageRepository(UserRepository userRepo) {
        this.userRepo = userRepo;
    }

    // Helpers
    // Load the list of people who received a specific message
    private void loadRecipients(List<Message> messages, Connection con) throws SQLException {
        if (messages.isEmpty())
            return;

        Map<Long, Message> msgMap = new HashMap<>();
        for (Message m: messages)
            msgMap.put(m.getId(), m);

        String placeholders = String.join(",", Collections.nCopies(messages.size(), "?"));

        String sql = """
                SELECT mr.id_message,
                       u."idUser", u.username, u.email, u.password,
                       p.name, p.firstName, p."birthDate", p.occupation,
                       d.speed, d.resistance, d.duck_type
                FROM public."MessageRecipients" mr
                JOIN public."Users" u ON mr.id_recipient = u."idUser"
                LEFT JOIN public."People" p ON u."idUser" = p."idPerson"
                LEFT JOIN public."Ducks" d ON u."idUser" = d."idDuck"
                WHERE mr.id_message IN (%s)
                """.formatted(placeholders);

        try (PreparedStatement ps = con.prepareStatement(sql)) {
            int idx = 1;
            for (Message m: messages)
                ps.setLong(idx++, m.getId());

            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    Long msgId = rs.getLong("id_message");
                    User recipient = PostgresUserRepository.mapRow(rs);

                    Message m = msgMap.get(msgId);
                    if (m != null)
                        m.getTo().add(recipient);
                }
            }
        }
    }

    private Message mapRow(ResultSet rs, Connection con) throws SQLException {
        Long id = rs.getLong("id_message");
        String text = rs.getString("message_text");
        LocalDateTime date = rs.getTimestamp("send_at").toLocalDateTime();

        User sender = PostgresUserRepository.mapRow(rs);

        Message replyMsg = null;
        Long replyId = rs.getLong("reply_to");

        if (!rs.wasNull()) {
            String replyText = rs.getString("reply_text");
            Long replySenderId = rs.getLong("reply_sender_id");
            String replySenderName = rs.getString("reply_sender_name");

            User replySender = new Person.Builder(replySenderId)
                    .username(replySenderName)
                    .build();

            replyMsg = new Message(replyId, replySender, new ArrayList<>(), replyText, null, null);
        }

        return new Message(id, sender, new ArrayList<>(), text, date, replyMsg);
    }

    @Override
    public void save(Message m) {
        String insertMsg = """
                INSERT INTO public."Messages"(from_user_id, message_text, send_at, reply_to)
                VALUES (?, ?, ?, ?) RETURNING id_message
                """;

        String insertRcpt = """
                INSERT INTO public."MessageRecipients"(id_message, id_recipient)
                VALUES (?, ?)
                """;

        try (Connection con = Db.getConnection()) {
            con.setAutoCommit(false);
            try {
                Long newId;
                try (PreparedStatement ps = con.prepareStatement(insertMsg)) {
                    ps.setLong(1, m.getFrom().getId());
                    ps.setString(2, m.getText());
                    ps.setTimestamp(3, Timestamp.valueOf(m.getDate()));

                    if (m.getReply() != null)
                        ps.setLong(4, m.getReply().getId());
                    else
                        ps.setNull(4, Types.BIGINT);

                    try (ResultSet rs = ps.executeQuery()) {
                        if (rs.next())
                            newId = rs.getLong(1);
                        else
                            throw new SQLException("Failed to insert message");
                    }
                }

                try (PreparedStatement ps = con.prepareStatement(insertRcpt)) {
                    for (User recipient : m.getTo()) {
                        ps.setLong(1, newId);
                        ps.setLong(2, recipient.getId());
                        ps.addBatch();  // Batch insert for performance
                    }
                    ps.executeBatch();
                }

                con.commit();
                m.setId(newId);
            } catch (SQLException e) {
                con.rollback();
                throw e;
            } finally {
                con.setAutoCommit(true);
            }
        } catch (SQLException e) {
            throw new DatabaseException("save message", e.getMessage());
        }
    }

    @Override
    public Message findById(Long id) {
        String sql = """
                SELECT m.*,
                    u."idUser", u.username, u.email, u.password,
                    p.name, p.firstName, p."birthDate", p.occupation,
                    d.speed, d.resistance, d.duck_type
                FROM public."Messages" m
                JOIN public."Users" u ON from_user_id = u."idUser"
                LEFT JOIN public."People" p ON u."idUser" = p."idPerson"
                LEFT JOIN public."Ducks" d ON u."idUser" = d."idDuck"
                WHERE m.id_message = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);

            try(ResultSet rs = ps.executeQuery()){
                if (rs.next()){
                    Message m = mapRow(rs, con);
                    loadRecipients(List.of(m), con);
                    return m;
                }
            }
        } catch (SQLException e) {
            return null;
        }
        return null;
    }

    @Override
    public List<Message> findConversation(Long u1, Long u2) {
        String sql = """
                SELECT DISTINCT m.*,
                                u."idUser", u.username, u.email, u.password,
                                p.name, p.firstName, p."birthDate", p.occupation,
                                d.speed, d.resistance, d.duck_type,
                                reply.message_text AS reply_text,
                                replyUser."idUser" AS reply_sender_id,
                                replyUser.username AS reply_sender_name
                
                FROM public."Messages" m
                JOIN public."Users" u ON m.from_user_id = u."idUser"
                LEFT JOIN public."People" p ON u."idUser" = p."idPerson"
                LEFT JOIN public."Ducks" d ON u."idUser" = d."idDuck"
                JOIN public."MessageRecipients" mr ON m.id_message = mr.id_message
                LEFT JOIN public."Messages" reply ON m.reply_to = reply.id_message
                LEFT JOIN public."Users" replyUser ON reply.from_user_id = replyUser."idUser"
                WHERE
                    (m.from_user_id = ? AND mr.id_recipient = ?)
                    OR
                    (m.from_user_id = ? AND mr.id_recipient = ?)
                ORDER BY m.send_at ASC
                """;

        List<Message> conversation = new ArrayList<>();
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, u1);
            ps.setLong(2, u2);
            ps.setLong(3, u2);
            ps.setLong(4, u1);

            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next())
                    conversation.add(mapRow(rs, con));
            }

            loadRecipients(conversation, con);
        } catch (SQLException e) {
            throw new DatabaseException("find conversation", e.getMessage());
        }

        return conversation;
    }
}
