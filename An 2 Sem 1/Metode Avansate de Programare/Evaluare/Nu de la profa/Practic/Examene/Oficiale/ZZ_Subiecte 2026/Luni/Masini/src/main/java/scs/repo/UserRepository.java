package scs.repo;

import scs.domain.User;
import scs.utilities.database.Db;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserRepository extends AbstractDbRepository<User> {
    @Override
    protected String getTableName() {
        return "public.\"Users\"";
    }

    @Override
    protected String getIdColumnName() {
        return "id";
    }

    @Override
    protected String getInsertSql() {
        return "INSERT INTO " + getTableName() + " (username, password, role) VALUES (?, ?, ?)";
    }

    @Override
    protected String getUpdateSql() {
        return "UPDATE " + getTableName() + " SET username = ?, password = ?, role = ? WHERE id = ?";
    }

    @Override
    protected User mapResultSet(ResultSet rs) throws SQLException {
        return new User(
                rs.getLong("id"),
                rs.getString("username"),
                rs.getString("password"),
                rs.getString("role")
        );
    }

    @Override
    protected void setInsertParams(PreparedStatement ps, User entity) throws SQLException {
        ps.setString(1, entity.getUsername());
        ps.setString(2, entity.getPassword());
        ps.setString(3, entity.getRole());
    }

    @Override
    protected void setUpdateParams(PreparedStatement ps, User entity) throws SQLException {
        ps.setString(1, entity.getUsername());
        ps.setString(2, entity.getPassword());
        ps.setString(3, entity.getRole());
        ps.setLong(4, entity.getId());
    }

    @Override
    protected void setIdFromDb(User entity, Long id) {
        entity.setId(id);
    }

    // find by username for login
    public User findByUsername(String username) {
        String sql = "SELECT * FROM " + getTableName() + " WHERE username = ?";
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, username);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next())
                    return mapResultSet(rs);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return null;
    }
}
