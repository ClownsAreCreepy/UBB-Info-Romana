package scs.repo;

import scs.domain.Car;
import scs.utilities.database.Db;

import javax.xml.transform.Result;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class CarRepository extends AbstractDbRepository<Car> {
    @Override
    protected String getTableName() {
        return "public.\"Cars\"";
    }

    @Override
    protected String getIdColumnName() {
        return "id";
    }

    @Override
    protected String getInsertSql() {
        return "INSERT INTO public.\"Cars\" (denumire, descriere, pret, status, comment) VALUES (?, ?, ?, ?, ?)";
    }

    @Override
    protected String getUpdateSql() {
        return "UPDATE public.\"Cars\" SET denumire=?, descriere=?, pret=?, status=?, comment=? WHERE id=?";
    }

    @Override
    protected Car mapResultSet(ResultSet rs) throws SQLException {
        return new Car(
                rs.getLong("id"),
                rs.getString("denumire"),
                rs.getString("descriere"),
                rs.getInt("pret"),
                rs.getString("status"),
                rs.getString("comment")
        );
    }

    @Override
    protected void setInsertParams(PreparedStatement ps, Car entity) throws SQLException {
        ps.setString(1, entity.getDenumire());
        ps.setString(2, entity.getDescriere());
        ps.setInt(3, entity.getPret());
        ps.setString(4, entity.getStatus());
        ps.setString(5, entity.getComment());
    }

    @Override
    protected void setUpdateParams(PreparedStatement ps, Car entity) throws SQLException {
        ps.setString(1, entity.getDenumire());
        ps.setString(2, entity.getDescriere());
        ps.setInt(3, entity.getPret());
        ps.setString(4, entity.getStatus());
        ps.setString(5, entity.getComment());
        ps.setLong(6, entity.getId());
    }

    @Override
    protected void setIdFromDb(Car entity, Long id) {
        entity.setId(id);
    }

    // SQL Filtering
    public List<Car> findByStatus(String status) {
        List<Car> list = new ArrayList<>();
        String sql = "SELECT * FROM " + getTableName() + " WHERE status = ?";
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, status);
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next())
                    list.add(mapResultSet(rs));
            }
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
        return list;
    }
}
