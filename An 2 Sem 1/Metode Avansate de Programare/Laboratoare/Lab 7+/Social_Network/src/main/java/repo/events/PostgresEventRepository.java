package repo.events;

import domain.event.Event;
import utilities.database.Db;
import utilities.errors.NotFoundException;

import java.sql.*;
import java.time.Instant;
import java.util.ArrayList;
import java.util.List;

public class PostgresEventRepository implements EventRepository {

    private final Db db;

    public PostgresEventRepository(Db db) {
        this.db = db;
    }

    // --------- mapping ---------
    private Event mapEvent(ResultSet rs) throws SQLException {
        long id = rs.getLong("idEvent");
        String name = rs.getString("name");

        Event e = new Event(id, name);

        Timestamp ts = rs.getTimestamp("last_notified_at");
        if (ts != null) {
            e.notifySubscribers(rs.getString("last_notification"));
        }

        return e;
    }

    private void loadSubscribers(Event e, Connection con) throws SQLException {
        String sql = """
            SELECT id_user FROM public."EventSubscribers"
            WHERE id_event = ?
        """;

        try (var ps = con.prepareStatement(sql)) {
            ps.setLong(1, e.getId());
            try (var rs = ps.executeQuery()) {
                while (rs.next()) {
                    long uid = rs.getLong("id_user");
                    e.getSubscribers().add(uid); // direct ID injection
                }
            }
        } catch (UnsupportedOperationException ignored) {
            // In case getSubscribers() returns unmodifiable set,
            // we would need a workaround inside Event (optional)
        }
    }

    // --------- CRUD ---------
    @Override
    public void add(Event e) {
        String sql = """
            INSERT INTO public."Events"(name, last_notified_at, last_notification)
            VALUES (?, ?, ?)
            RETURNING "idEvent"
        """;

        try (var con = db.connect();
             var ps = con.prepareStatement(sql)) {

            ps.setString(1, e.getName());

            if (e.getLastNotifiedAt() == null)
                ps.setNull(2, Types.TIMESTAMP);
            else
                ps.setTimestamp(2, Timestamp.from(e.getLastNotifiedAt()));

            ps.setString(3, e.getLastNotification());

            try (var rs = ps.executeQuery()) {
                if (rs.next()) {
                    long newId = rs.getLong(1);
                    // update the event's ID if needed
                }
            }

        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    @Override
    public void update(Event e) {
        String sql = """
            UPDATE public."Events"
            SET name = ?, last_notified_at = ?, last_notification = ?
            WHERE "idEvent" = ?
        """;

        try (var con = db.connect();
             var ps = con.prepareStatement(sql)) {

            ps.setString(1, e.getName());

            if (e.getLastNotifiedAt() == null)
                ps.setNull(2, Types.TIMESTAMP);
            else
                ps.setTimestamp(2, Timestamp.from(e.getLastNotifiedAt()));

            ps.setString(3, e.getLastNotification());
            ps.setLong(4, e.getId());

            if (ps.executeUpdate() == 0)
                throw new NotFoundException("event", "event not found.");

        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    @Override
    public void delete(long id) {
        String sql = """
            DELETE FROM public."Events"
            WHERE "idEvent" = ?
        """;

        try (var con = db.connect();
             var ps = con.prepareStatement(sql)) {

            ps.setLong(1, id);

            if (ps.executeUpdate() == 0)
                throw new NotFoundException("event", "event not found.");

        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    @Override
    public Event findById(long id) {
        String sql = """
            SELECT * FROM public."Events"
            WHERE "idEvent" = ?
        """;

        try (var con = db.connect();
             var ps = con.prepareStatement(sql)) {

            ps.setLong(1, id);

            try (var rs = ps.executeQuery()) {
                if (!rs.next())
                    throw new NotFoundException("event", "event not found.");

                Event e = mapEvent(rs);
                loadSubscribers(e, con);
                return e;
            }

        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    @Override
    public List<Event> getAll() {
        String sql = """
            SELECT * FROM public."Events"
        """;

        try (var con = db.connect();
             var st = con.createStatement();
             var rs = st.executeQuery(sql)) {

            List<Event> list = new ArrayList<>();

            while (rs.next()) {
                Event e = mapEvent(rs);
                loadSubscribers(e, con);
                list.add(e);
            }

            return list;

        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    // --------- SUBSCRIBERS ---------
    @Override
    public void addSubscriber(long eventId, long userId) {
        String sql = """
            INSERT INTO public."EventSubscribers"(id_event, id_user)
            VALUES (?, ?)
            ON CONFLICT DO NOTHING
        """;

        try (var con = db.connect();
             var ps = con.prepareStatement(sql)) {

            ps.setLong(1, eventId);
            ps.setLong(2, userId);
            ps.executeUpdate();

        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    @Override
    public void removeSubscriber(long eventId, long userId) {
        String sql = """
            DELETE FROM public."EventSubscribers"
            WHERE id_event = ? AND id_user = ?
        """;

        try (var con = db.connect();
             var ps = con.prepareStatement(sql)) {

            ps.setLong(1, eventId);
            ps.setLong(2, userId);
            ps.executeUpdate();

        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }
}
