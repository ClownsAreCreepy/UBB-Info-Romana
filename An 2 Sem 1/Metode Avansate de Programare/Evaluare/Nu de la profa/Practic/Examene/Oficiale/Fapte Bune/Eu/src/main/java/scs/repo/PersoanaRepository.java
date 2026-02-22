package scs.repo;

import scs.domain.Oras;
import scs.domain.Persoana;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PersoanaRepository extends AbstractDbRepository<Persoana> {
    @Override
    protected String getTableName() {
        return "persoana";
    }

    @Override
    protected String getIdColumnName() {
        return "id";
    }

    @Override
    protected String getInsertSql() {
        return "INSERT INTO persoana (nume, prenume, username, parola, oras, strada, numar_strada, telefon) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
    }

    @Override
    protected String getUpdateSql() {
        return "UPDATE persoana SET nume=?, prenume=?, username=?, parola=?, oras=?, strada=?, numar_strada=?, telefon=? WHERE id=?";
    }

    @Override
    protected Persoana mapResultSet(ResultSet rs) throws SQLException {
        return new Persoana(
                rs.getLong("id"),
                rs.getString("nume"),
                rs.getString("prenume"),
                rs.getString("username"),
                rs.getString("parola"),
                Oras.valueOf(rs.getString("oras")),
                rs.getString("strada"),
                rs.getString("numar_strada"),
                rs.getString("telefon")
        );
    }

    @Override
    protected void setInsertParams(PreparedStatement ps, Persoana entity) throws SQLException {
        ps.setString(1, entity.getNume());
        ps.setString(2, entity.getPrenume());
        ps.setString(3, entity.getUsername());
        ps.setString(4, entity.getParola());
        ps.setString(5, entity.getOras().name());
        ps.setString(6, entity.getStrada());
        ps.setString(7, entity.getNumar_strada());
        ps.setString(8, entity.getTelefon());
    }

    @Override
    protected void setUpdateParams(PreparedStatement ps, Persoana entity) throws SQLException {
        setInsertParams(ps, entity);
        ps.setLong(9, entity.getId());
    }

    @Override
    protected void setIdFromDb(Persoana entity, Long id) {
        entity.setId(id);
    }
}
