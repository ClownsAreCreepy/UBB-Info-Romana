package scs.repo.friend.requests;

import scs.domain.interactions.FriendRequest;
import scs.domain.interactions.RequestStatus;
import scs.domain.user.User;
import scs.repo.users.PostgresUserRepository;
import scs.repo.users.UserRepository;
import scs.utilities.database.Db;
import scs.utilities.errors.DatabaseException;
import scs.utilities.errors.NotFoundException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class PostgresRequestRepository implements RequestRepository {
    private final UserRepository userRepo;

    public PostgresRequestRepository(UserRepository userRepo) {
        this.userRepo = userRepo;
    }

    private FriendRequest mapRow(ResultSet rs) throws SQLException {
        Long id = rs.getLong("id_request");
        Long fromId = rs.getLong("from_user_id");
        Long toId = rs.getLong("to_user_id");
        String status = rs.getString("status");
        LocalDateTime date = rs.getTimestamp("date").toLocalDateTime();

        User from = userRepo.findById(fromId);
        User to = userRepo.findById(toId);
        return new FriendRequest(id, from, to, RequestStatus.valueOf(status), date);
    }

    private FriendRequest mapRowWithUser(ResultSet rs, User toUser) throws SQLException {
        Long id = rs.getLong("id_request");
        String status = rs.getString("status");
        LocalDateTime date = rs.getTimestamp("date").toLocalDateTime();

        User from = PostgresUserRepository.mapRow(rs);
        return new FriendRequest(id, from, toUser, RequestStatus.valueOf(status), date);
    }

    @Override
    public void save(FriendRequest req) {
        String sql = """
                INSERT INTO public."FriendRequests" (from_user_id, to_user_id, status, date)
                VALUES (?, ?, ?::request_status, ?)
                RETURNING id_request
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, req.getFrom().getId());
            ps.setLong(2, req.getTo().getId());
            ps.setString(3, req.getStatus().name());
            ps.setTimestamp(4, Timestamp.valueOf(req.getDate()));

            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next())
                    req.setId(rs.getLong("id_request"));
            }
        } catch (SQLException e) {
            if (e.getSQLState().equals("23505"))
                throw new DatabaseException("duplicate request", "Request already exists");
            throw new DatabaseException("save request", e.getMessage());
        }
    }

    @Override
    public void update(FriendRequest req) {
        String sql = """
                UPDATE public."FriendRequests"
                SET status = ?::request_status
                WHERE id_request = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, req.getStatus().name());
            ps.setLong(2, req.getId());

            if (ps.executeUpdate() == 0)
                throw new NotFoundException("request", "Request not found");
        } catch (SQLException e) {
            throw new DatabaseException("update request", e.getMessage());
        }
    }

    @Override
    public void delete(FriendRequest req) {
        String sql = """
                DELETE FROM public."FriendRequests"
                WHERE id_request = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, req.getId());
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new DatabaseException("delete request", e.getMessage());
        }
    }

    @Override
    public FriendRequest findOne(Long fromId, Long toId) {
        String sql = """
                SELECT * FROM public."FriendRequests"
                WHERE from_user_id = ? AND to_user_id = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, fromId);
            ps.setLong(2, toId);

            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next())
                    return mapRow(rs);
            }
        } catch (SQLException e) {
            throw new DatabaseException("find request", e.getMessage());
        }

        return null;
    }

    @Override
    public List<FriendRequest> findPending(Long toUserId) {
        User toUser = userRepo.findById(toUserId);
        if (toUser == null)
            throw new NotFoundException("user", "User " + toUserId + " not found");

        String sql = """
                SELECT
                    r.id_request, r.status, r.date,
                    u."idUser", u.username, u.email, u.password,
                    p.name, p.firstname, p."birthDate", p.occupation,
                    d.speed, d.resistance, d.duck_type
                FROM public."FriendRequests" r
                JOIN public."Users" u ON r.from_user_id = u."idUser"
                LEFT JOIN public."People" p ON p."idPerson" = u."idUser"
                LEFT JOIN public."Ducks" d ON d."idDuck" = u."idUser"
                WHERE r.to_user_id = ? AND r.status = 'PENDING'
                ORDER BY r.date DESC
                """;

        List<FriendRequest> list = new ArrayList<>();

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, toUserId);

            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next())
                    list.add(mapRowWithUser(rs, toUser));
            }
        } catch (SQLException e) {
            throw new DatabaseException("find pending", e.getMessage());
        }

        return list;
    }
}
