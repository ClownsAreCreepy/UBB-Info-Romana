package repo.friendships;

import utilities.database.Db;

import java.sql.*;
import java.util.*;

public class PostgresFriendshipRepository implements FriendshipRepository {
    private final Db db;

    public PostgresFriendshipRepository(Db db) { this.db = db; }

    @Override
    public void addUser(long id) { /* not needed in SQL impl */ }

    @Override
    public void removeUser(long id) {
        String sql = """
            DELETE FROM public."Friendships"
            WHERE id_1 = ? OR id_2 = ?
        """;
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            ps.setLong(2, id);
            ps.executeUpdate();
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public void addFriendship(long id1, long id2) {
        String sql = """
            INSERT INTO public."Friendships"(id_1, id_2)
            VALUES (LEAST(?,?), GREATEST(?,?))
        """;
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id1);
            ps.setLong(2, id2);
            ps.setLong(3, id1);
            ps.setLong(4, id2);
            ps.executeUpdate();
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public void removeFriendship(long id1, long id2) {
        String sql = """
            DELETE FROM public."Friendships"
            WHERE (id_1 = LEAST(?,?) AND id_2 = GREATEST(?,?))
                OR (id_1 = GREATEST(?,?) AND id_2 = LEAST(?,?))
        """;
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id1);
            ps.setLong(2, id2);
            ps.setLong(3, id1);
            ps.setLong(4, id2);
            ps.setLong(5, id1);
            ps.setLong(6, id2);
            ps.setLong(7, id1);
            ps.setLong(8, id2);
            ps.executeUpdate();
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public Set<Long> getFriends(long id) {
        String sql = """
            SELECT id_2 AS friend_id FROM public."Friendships" WHERE id_1 = ?
            UNION
            SELECT id_1 AS friend_id FROM public."Friendships" WHERE id_2 = ?
        """;
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            ps.setLong(2, id);
            try (var rs = ps.executeQuery()) {
                var set = new LinkedHashSet<Long>();
                while (rs.next()) set.add(rs.getLong("friend_id"));
                return set;
            }
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public Set<Long> getAllUsers() {
        String sql = """
            SELECT id_1 FROM public."Friendships"
            UNION
            SELECT id_2 FROM public."Friendships"
        """;
        try (var con = db.connect(); var st = con.createStatement(); var rs = st.executeQuery(sql)) {
            var set = new LinkedHashSet<Long>();
            while (rs.next()) set.add(rs.getLong(1));
            return set;
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public boolean areFriends(long id1, long id2) {
        String sql = """
            SELECT 1 FROM public."Friendships"
            WHERE id_1 = LEAST(?,?) AND id_2 = GREATEST(?,?)
            LIMIT 1
        """;
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id1);
            ps.setLong(2, id2);
            ps.setLong(3, id1);
            ps.setLong(4, id2);
            try (var rs = ps.executeQuery()) { return rs.next(); }
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public int nrFriends(long id) {
        String sql = """
            SELECT COUNT(*) FROM public."Friendships"
            WHERE id_1 = ? OR id_2 = ?
        """;
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            ps.setLong(2, id);
            try (var rs = ps.executeQuery()) { rs.next(); return rs.getInt(1); }
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public List<long[]> findAllEdges() {
        String sql = """
                SELECT id_1, id_2 FROM public."Friendships"
               """;
        try (var con = db.connect(); var st = con.createStatement(); var rs = st.executeQuery(sql)) {
            var list = new ArrayList<long[]>();
            while (rs.next()) list.add(new long[]{rs.getLong(1), rs.getLong(2)});
            return list;
        } catch (SQLException e) { throw new RuntimeException(e); }
    }
}
