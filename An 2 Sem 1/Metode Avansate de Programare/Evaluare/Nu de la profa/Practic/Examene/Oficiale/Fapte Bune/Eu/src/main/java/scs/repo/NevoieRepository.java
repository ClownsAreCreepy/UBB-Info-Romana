package scs.repo;

import scs.domain.Nevoie;

import java.sql.*;

public class NevoieRepository extends AbstractDbRepository<Nevoie> {
    @Override
    protected String getTableName() {
        return "nevoie";
    }

    @Override
    protected String getIdColumnName() {
        return "id";
    }

    @Override
    protected String getInsertSql() {
        return "INSERT INTO nevoie (titlu, descriere, deadline, om_in_nevoie, om_salvator, status) VALUES (?, ?, ?, ?, ?, ?)";
    }

    @Override
    protected String getUpdateSql() {
        return "UPDATE nevoie SET titlu=?, descriere=?, deadline=?, om_in_nevoie=?, om_salvator=?, status=? WHERE id=?";
    }

    @Override
    protected Nevoie mapResultSet(ResultSet rs) throws SQLException {
        long salvatorId = rs.getLong("om_salvator");
        Long omSalvator = rs.wasNull() ? null : salvatorId;

        return new Nevoie(
                rs.getLong("id"),
                rs.getString("titlu"),
                rs.getString("descriere"),
                rs.getTimestamp("deadline").toLocalDateTime(),
                rs.getLong("om_in_nevoie"),
                omSalvator,
                rs.getString("status")
        );
    }

    @Override
    protected void setInsertParams(PreparedStatement ps, Nevoie entity) throws SQLException {
        ps.setString(1, entity.getTitlu());
        ps.setString(2, entity.getDescriere());
        ps.setTimestamp(3, Timestamp.valueOf(entity.getDeadline()));
        ps.setLong(4, entity.getOmInNevoie());

        if (entity.getOmSalvator() != null)
            ps.setLong(5, entity.getOmSalvator());
        else
            ps.setNull(5, Types.BIGINT);

        ps.setString(6, entity.getStatus());
    }

    @Override
    protected void setUpdateParams(PreparedStatement ps, Nevoie entity) throws SQLException {
        setInsertParams(ps, entity);
        ps.setLong(7, entity.getId());
    }

    @Override
    protected void setIdFromDb(Nevoie entity, Long id) {
        entity.setId(id);
    }
}
