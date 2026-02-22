package scs.repo;

import scs.domain.User;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserRepository extends AbstractDbRepository<User> {
    @Override
    protected String getTableName() {
        return "public.users";
    }

    @Override
    protected String getIdColumnName() {
        return "id";
    }

    @Override
    protected String getInsertSql() {
        return "INSERT INTO public.users (name, budget) VALUES (?, ?)";
    }

    @Override
    protected String getUpdateSql() {
        return "UPDATE public.users SET name = ?, budget = ? WHERE id = ?";
    }

    @Override
    protected User mapResultSet(ResultSet rs) throws SQLException {
        return new User(rs.getLong("id"),
                rs.getString("name"),
                rs.getDouble("budget")
        );
    }

    @Override
    protected void setInsertParams(PreparedStatement ps, User entity) throws SQLException {
        ps.setString(1, entity.getName());
        ps.setDouble(2, entity.getBudget());
    }

    @Override
    protected void setUpdateParams(PreparedStatement ps, User entity) throws SQLException {
        ps.setString(1, entity.getName());
        ps.setDouble(2, entity.getBudget());
        ps.setLong(3, entity.getId());
    }

    @Override
    protected void setIdFromDb(User entity, Long id) {
        entity.setId(id);
    }
}
