package scs.repo;

import scs.domain.Transaction;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;

public class TransactionRepository extends AbstractDbRepository<Transaction> {
    @Override
    protected String getTableName() {
        return "public.transactions";
    }

    @Override
    protected String getIdColumnName() {
        return "id";
    }

    @Override
    protected String getInsertSql() {
        return "INSERT INTO public.transactions (userid, coinsymbol, type, price, timestamp) VALUES (?, ?, ?, ?, ?)";
    }

    @Override
    protected String getUpdateSql() {
        return ""; // immutable
    }

    @Override
    protected Transaction mapResultSet(ResultSet rs) throws SQLException {
        return new Transaction(
                rs.getLong("id"),
                rs.getLong("userid"),
                rs.getString("coinsymbol"),
                rs.getString("type"),
                rs.getDouble("price"),
                rs.getTimestamp("timestamp").toLocalDateTime()
        );
    }

    @Override
    protected void setInsertParams(PreparedStatement ps, Transaction entity) throws SQLException {
        ps.setLong(1, entity.getUserid());
        ps.setString(2, entity.getCoinsymbol());
        ps.setString(3, entity.getType());
        ps.setDouble(4, entity.getPrice());
        ps.setTimestamp(5, Timestamp.valueOf(entity.getTimestamp()));
    }

    @Override
    protected void setUpdateParams(PreparedStatement ps, Transaction entity) throws SQLException {
        // not needed
    }

    @Override
    protected void setIdFromDb(Transaction entity, Long id) {
        entity.setId(id);
    }
}
