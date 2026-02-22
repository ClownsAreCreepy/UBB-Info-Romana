package scs.repo;

import scs.utilities.database.Db;
import scs.utilities.paging.Page;
import scs.utilities.paging.Pageable;
import java.sql.*;
import java.util.*;

public abstract class AbstractDbRepository<E> implements Repository<E> {

    protected abstract String getTableName();      // e.g. "public.drivers"
    protected abstract String getIdColumnName();   // e.g. "id_driver"

    protected abstract String getInsertSql();
    protected abstract String getUpdateSql();
    protected abstract E mapResultSet(ResultSet rs) throws SQLException;
    protected abstract void setInsertParams(PreparedStatement ps, E entity) throws SQLException;
    protected abstract void setUpdateParams(PreparedStatement ps, E entity) throws SQLException;
    protected abstract void setIdFromDb(E entity, Long id);

    // --- GENERIC IMPLEMENTATION ---

    @Override
    public Optional<E> findOne(Long id) {
        String sql = "SELECT * FROM " + getTableName() + " WHERE " + getIdColumnName() + " = ?";
        try (Connection con = Db.getConnection();
             PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) return Optional.of(mapResultSet(rs));
            }
        } catch (SQLException e) { throw new RuntimeException(e.getMessage()); }
        return Optional.empty();
    }

    @Override
    public List<E> findAll() {
        List<E> list = new ArrayList<>();
        try (Connection con = Db.getConnection();
             PreparedStatement ps = con.prepareStatement("SELECT * FROM " + getTableName());
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) list.add(mapResultSet(rs));
        } catch (SQLException e) { throw new RuntimeException(e.getMessage()); }
        return list;
    }

    @Override
    public Page<E> findAll(Pageable pageable) {
        String sql = "SELECT * FROM " + getTableName() + " LIMIT ? OFFSET ?";
        List<E> list = new ArrayList<>();
        try (Connection con = Db.getConnection();
             PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setInt(1, pageable.getPageSize());
            ps.setInt(2, pageable.getOffset());
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) list.add(mapResultSet(rs));
            }
        } catch (SQLException e) { throw new RuntimeException(e.getMessage()); }
        return new Page<>(list, 0, pageable.getPageSize());
    }

    @Override
    public E save(E entity) {
        try (Connection con = Db.getConnection();
             PreparedStatement ps = con.prepareStatement(getInsertSql(), Statement.RETURN_GENERATED_KEYS)) {
            setInsertParams(ps, entity);
            ps.executeUpdate();
            try (ResultSet rs = ps.getGeneratedKeys()) {
                if (rs.next()) setIdFromDb(entity, rs.getLong(1));
            }
        } catch (SQLException e) { throw new RuntimeException(e.getMessage()); }
        return entity;
    }

    @Override
    public void update(E entity) {
        try (Connection con = Db.getConnection();
             PreparedStatement ps = con.prepareStatement(getUpdateSql())) {
            setUpdateParams(ps, entity);
            ps.executeUpdate();
        } catch (SQLException e) { throw new RuntimeException(e.getMessage()); }
    }

    @Override
    public void delete(Long id) {
        String sql = "DELETE FROM " + getTableName() + " WHERE " + getIdColumnName() + " = ?";
        try (Connection con = Db.getConnection();
             PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            ps.executeUpdate();
        } catch (SQLException e) { throw new RuntimeException(e.getMessage()); }
    }
}