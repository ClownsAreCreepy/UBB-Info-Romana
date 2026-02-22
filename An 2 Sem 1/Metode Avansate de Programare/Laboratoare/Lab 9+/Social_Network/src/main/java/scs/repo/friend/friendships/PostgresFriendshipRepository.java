package scs.repo.friend.friendships;

import scs.utilities.database.Db;
import scs.utilities.errors.DatabaseException;

import java.sql.*;
import java.util.*;

public class PostgresFriendshipRepository implements FriendshipRepository {
    public PostgresFriendshipRepository() {
    }

    @Override
    public void addUser(Long id) { /* not needed in SQL impl */ }

    @Override
    public void removeUser(Long id) {
        String sql = """
                    DELETE FROM public."Friendships"
                    WHERE id_1 = ? OR id_2 = ?
                """;
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            ps.setLong(2, id);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new DatabaseException("remove user", e.getMessage());
        }
    }

    @Override
    public void addFriendship(Long id1, Long id2) {
        String sql = """
                    INSERT INTO public."Friendships"(id_1, id_2)
                    VALUES (LEAST(?,?), GREATEST(?,?))
                """;
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id1);
            ps.setLong(2, id2);
            ps.setLong(3, id1);
            ps.setLong(4, id2);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new DatabaseException("add friendship", e.getMessage());
        }
    }

    @Override
    public void removeFriendship(Long id1, Long id2) {
        String sql = """
                    DELETE FROM public."Friendships"
                    WHERE id_1 = LEAST(?,?) AND id_2 = GREATEST(?,?)
                """;
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id1);
            ps.setLong(2, id2);
            ps.setLong(3, id1);
            ps.setLong(4, id2);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new DatabaseException("remove friendship", e.getMessage());
        }
    }

    @Override
    public Set<Long> getFriends(Long id) {
        String sql = """
                    SELECT id_2 AS friend_id FROM public."Friendships" WHERE id_1 = ?
                    UNION
                    SELECT id_1 AS friend_id FROM public."Friendships" WHERE id_2 = ?
                """;
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            ps.setLong(2, id);
            try (ResultSet rs = ps.executeQuery()) {
                Set<Long> set = new LinkedHashSet<>();
                while (rs.next()) set.add(rs.getLong("friend_id"));
                return set;
            }
        } catch (SQLException e) {
            throw new DatabaseException("get friends", e.getMessage());
        }
    }

    @Override
    public Set<Long> getAllUsers() {
        String sql = """
                    SELECT id_1 FROM public."Friendships"
                    UNION
                    SELECT id_2 FROM public."Friendships"
                """;
        try (Connection con = Db.getConnection(); Statement st = con.createStatement(); ResultSet rs = st.executeQuery(sql)) {
            Set<Long> set = new LinkedHashSet<>();
            while (rs.next()) set.add(rs.getLong(1));
            return set;
        } catch (SQLException e) {
            throw new DatabaseException("get all users", e.getMessage());
        }
    }

    @Override
    public boolean areFriends(Long id1, Long id2) {
        String sql = """
                    SELECT 1 FROM public."Friendships"
                    WHERE id_1 = LEAST(?,?) AND id_2 = GREATEST(?,?)
                """;
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id1);
            ps.setLong(2, id2);
            ps.setLong(3, id1);
            ps.setLong(4, id2);
            try (ResultSet rs = ps.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            throw new DatabaseException("check friendship", e.getMessage());
        }
    }

    @Override
    public int nrFriends(Long id) {
        String sql = """
                    SELECT COUNT(*) FROM public."Friendships"
                    WHERE id_1 = ? OR id_2 = ?
                """;
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            ps.setLong(2, id);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next())
                    return rs.getInt(1);
                return 0;
            }
        } catch (SQLException e) {
            throw new DatabaseException("count friends", e.getMessage());
        }
    }

    @Override
    public List<Long[]> findAllEdges() {
        String sql = """
                 SELECT id_1, id_2 FROM public."Friendships"
                """;
        try (Connection con = Db.getConnection(); Statement st = con.createStatement(); ResultSet rs = st.executeQuery(sql)) {
            List<Long[]> list = new ArrayList<>();
            while (rs.next()) list.add(new Long[]{rs.getLong(1), rs.getLong(2)});
            return list;
        } catch (SQLException e) {
            throw new DatabaseException("find edges", e.getMessage());
        }
    }
}
