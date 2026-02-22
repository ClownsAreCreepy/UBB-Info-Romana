package scs.repo;

import scs.domain.Coin;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CoinRepository extends AbstractDbRepository<Coin> {

    @Override
    protected String getTableName() {
        return "public.coins";
    }

    // Works because we'll only use it for findAll()
    // We will not use findOne(Long), thus we dont need an id of type Long
    @Override
    protected String getIdColumnName() {
        return "id";
    }

    @Override
    protected String getInsertSql() {
        return "INSERT INTO public.coins (id, name, price) VALUES (?, ?, ?)";
    }

    @Override
    protected String getUpdateSql() {
        return "UPDATE  public.coins SET price=? WHERE id=?";
    }

    @Override
    protected Coin mapResultSet(ResultSet rs) throws SQLException {
        return new Coin(rs.getString("id"), rs.getString("name"), rs.getDouble("price"));
    }

    @Override
    protected void setInsertParams(PreparedStatement ps, Coin entity) throws SQLException {
        ps.setString(1, entity.getSymbol());
        ps.setString(2, entity.getName());
        ps.setDouble(3, entity.getPrice());
    }

    @Override
    protected void setUpdateParams(PreparedStatement ps, Coin entity) throws SQLException {
        ps.setDouble(1, entity.getPrice());
        ps.setString(2, entity.getSymbol());
    }

    @Override
    protected void setIdFromDb(Coin entity, Long id) {

    }
}
