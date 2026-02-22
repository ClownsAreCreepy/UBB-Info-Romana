package scs.repo.events;

import scs.domain.event.Event;
import scs.utilities.database.Db;
import scs.utilities.errors.DatabaseException;
import scs.utilities.errors.NotFoundException;

import java.sql.*;
import java.util.*;

public class PostgresEventRepository implements EventRepository {
    public PostgresEventRepository() {
    }

    // --------- mapping ---------
    private Event mapEvent(ResultSet rs) throws SQLException {
        Long id = rs.getLong("idEvent");
        String name = rs.getString("name");

        return new Event(id, name);
    }

    private void loadSubscribers(Event e, Connection con) throws SQLException {
        String sql = """
                    SELECT id_user FROM public."EventSubscribers"
                    WHERE id_event = ?
                """;

        try (PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, e.getId());
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    Long uid = rs.getLong("id_user");
                    e.subscribeById(uid);
                }
            }
        }
    }

    private void loadSubscribersForMultipleEvents(List<Event> events, Connection con) throws SQLException {
        if (events.isEmpty())
            return;

        Map<Long, Event> eventMap = new HashMap<>();
        for (Event e : events)
            eventMap.put(e.getId(), e);

        String placeholders = String.join(",", Collections.nCopies(events.size(), "?"));
        String sql = String.format("""
                SELECT id_event, id_user
                FROM public."EventSubscribers"
                WHERE id_event IN (%s)
                """, placeholders);

        try (PreparedStatement ps = con.prepareStatement(sql)) {
            int index = 1;
            for (Event e : events)
                ps.setLong(index++, e.getId());

            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    Long eventId = rs.getLong("id_event");
                    Long userId = rs.getLong("id_user");

                    Event e = eventMap.get(eventId);
                    if (e != null)
                        e.subscribeById(userId);
                }
            }
        }
    }


    @Override
    public void add(Event e) {
        String sql = """
                    INSERT INTO public."Events"(name)
                    VALUES (?)
                    RETURNING "idEvent"
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {

            ps.setString(1, e.getName());
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    e.setId(rs.getLong("idEvent"));
                }
            }
        } catch (SQLException ex) {
            throw new DatabaseException("add event", ex.getMessage());
        }
    }

    @Override
    public void update(Event e) {
        String sql = """
                    UPDATE public."Events"
                    SET name = ?
                    WHERE "idEvent" = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {

            ps.setString(1, e.getName());
            ps.setLong(2, e.getId());

            if (ps.executeUpdate() == 0)
                throw new NotFoundException("event", "event not found.");

        } catch (SQLException ex) {
            throw new DatabaseException("update event", ex.getMessage());
        }
    }

    @Override
    public void delete(Long id) {
        String sql = """
                    DELETE FROM public."Events"
                    WHERE "idEvent" = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);

            if (ps.executeUpdate() == 0)
                throw new NotFoundException("event", "event not found.");

        } catch (SQLException ex) {
            throw new DatabaseException("delete event", ex.getMessage());
        }
    }

    @Override
    public Event findById(Long id) {
        String sql = """
                    SELECT * FROM public."Events"
                    WHERE "idEvent" = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);

            try (ResultSet rs = ps.executeQuery()) {
                if (!rs.next())
                    throw new NotFoundException("event", "event not found.");

                Event e = mapEvent(rs);
                loadSubscribers(e, con);
                return e;
            }

        } catch (SQLException ex) {
            throw new DatabaseException("find event", ex.getMessage());
        }
    }

    @Override
    public List<Event> getAll() {
        String sql = """
                    SELECT * FROM public."Events"
                """;

        try (Connection con = Db.getConnection(); Statement st = con.createStatement(); ResultSet rs = st.executeQuery(sql)) {
            List<Event> list = new ArrayList<>();

            while (rs.next())
                list.add(mapEvent(rs));

            loadSubscribersForMultipleEvents(list, con);

            return list;
        } catch (SQLException ex) {
            throw new DatabaseException("get all events", ex.getMessage());
        }
    }


    @Override
    public void addSubscriber(Long eventId, Long userId) {
        String sql = """
                    INSERT INTO public."EventSubscribers"(id_event, id_user)
                    VALUES (?, ?)
                    ON CONFLICT DO NOTHING
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, eventId);
            ps.setLong(2, userId);
            ps.executeUpdate();

        } catch (SQLException ex) {
            throw new DatabaseException("add event sub", ex.getMessage());
        }
    }

    @Override
    public void removeSubscriber(Long eventId, Long userId) {
        String sql = """
                    DELETE FROM public."EventSubscribers"
                    WHERE id_event = ? AND id_user = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, eventId);
            ps.setLong(2, userId);
            ps.executeUpdate();

        } catch (SQLException ex) {
            throw new DatabaseException("remove event sub", ex.getMessage());
        }
    }
}