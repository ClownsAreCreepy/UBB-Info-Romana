package repo.users;

import domain.user.*;
import utilities.database.Db;
import utilities.errors.DuplicateException;
import utilities.errors.NotFoundException;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class PostgresUserRepository implements UserRepository {
    private final Db db;

    public PostgresUserRepository(Db db) { this.db = db; }

    // ---------- mapping ----------
    private static User mapRow(ResultSet rs) throws SQLException {
        long id = rs.getLong("idUser");
        String username = rs.getString("username");
        String email = rs.getString("email");
        String password = rs.getString("password");

        // People
        String nume = rs.getString("nume");
        String prenume = rs.getString("prenume");
        Date dn = rs.getDate("dataNasterii");
        String ocup = rs.getString("ocupatie");

        // Ducks (nullable)
        Double viteza = rs.getObject("viteza", Double.class);
        Double rez = rs.getObject("rezistenta", Double.class);
        String duckType = rs.getString("tip_rata");

        boolean hasPerson = (nume != null) || (prenume != null) || (dn != null) || (ocup != null);
        boolean hasDuck   = (viteza != null) || (rez != null) || (duckType != null);

        if (hasPerson) {
            LocalDate birth = (dn == null ? null : dn.toLocalDate());
            return new Person(id, username, email, password, nume, prenume, birth, ocup);
        }

        if (hasDuck) {
            double v = (viteza == null ? 0.0 : viteza);
            double r = (rez == null ? 0.0 : rez);
            return switch (duckType) {
                case "SWIMMING" -> new SwimmingDuck(id, username, email, password, v, r);
                case "FLYING"   -> new FlyingDuck(id,   username, email, password, v, r);
                case "HYBRID"   -> new HybridDuck(id,   username, email, password, v, r);
                default -> throw new IllegalStateException("duck without valid tip_rata");
            };
        }

        // default bare Person
        return new Person(id, username, email, password, null, null, null, null);
    }

    // ---------- insert/update helpers ----------
    private static void insertUser(Connection con, User u) throws SQLException {
        try (var ps = con.prepareStatement("""
            INSERT INTO public."Users"("idUser", username, email, password)
            VALUES (?, ?, ?, ?)
        """)) {
            ps.setLong(1, u.getId());
            ps.setString(2, u.getUsername());
            ps.setString(3, u.getEmail());
            ps.setString(4, u.getPassword());
            ps.executeUpdate();
        }
    }

    private static void insertPerson(Connection con, Person p) throws SQLException {
        try (var ps = con.prepareStatement("""
            INSERT INTO public."People"("idPersoana", nume, prenume, "dataNasterii", ocupatie)
            VALUES (?, ?, ?, ?, ?)
        """)) {
            ps.setLong(1, p.getId());
            ps.setString(2, p.getNume());
            ps.setString(3, p.getPrenume());
            if (p.getDataNasterii() != null)
                ps.setDate(4, Date.valueOf(p.getDataNasterii()));
            else
                ps.setNull(4, Types.DATE);
            ps.setString(5, p.getOcupatie());
            ps.executeUpdate();
        }
    }

    private static void insertDuck(Connection con, Duck d) throws SQLException {
        String kind = (d instanceof SwimmingDuck) ? "SWIMMING"
                : (d instanceof FlyingDuck)   ? "FLYING"
                : (d instanceof HybridDuck)   ? "HYBRID" : null;

        try (var ps = con.prepareStatement("""
            INSERT INTO public."Ducks"("idDuck", viteza, rezistenta, tip_rata)
            VALUES (?, ?, ?, ?)
        """)) {
            ps.setLong(1, d.getId());
            ps.setObject(2, d.getViteza(), Types.DOUBLE);
            ps.setObject(3, d.getRezistenta(), Types.DOUBLE);
            ps.setString(4, kind);
            ps.executeUpdate();
        }
    }

    private static void updateUser(Connection con, User u) throws SQLException {
        try (var ps = con.prepareStatement("""
            UPDATE public."Users"
               SET username=?, email=?, password=?
             WHERE "idUser"=?
        """)) {
            ps.setString(1, u.getUsername());
            ps.setString(2, u.getEmail());
            ps.setString(3, u.getPassword());
            ps.setLong(4, u.getId());
            if (ps.executeUpdate() == 0)
                throw new NotFoundException("user", "user does not exist.");
        }
    }

    private static void upsertPerson(Connection con, Person p) throws SQLException {
        try (var ps = con.prepareStatement("""
            UPDATE public."People"
               SET nume=?, prenume=?, "dataNasterii"=?, ocupatie=?
             WHERE "idPersoana"=?
        """)) {
            ps.setString(1, p.getNume());
            ps.setString(2, p.getPrenume());
            if (p.getDataNasterii() != null)
                ps.setDate(3, Date.valueOf(p.getDataNasterii()));
            else
                ps.setNull(3, Types.DATE);
            ps.setString(4, p.getOcupatie());
            ps.setLong(5, p.getId());
            int n = ps.executeUpdate();
            if (n == 0) insertPerson(con, p);
        }
    }

    private static void upsertDuck(Connection con, Duck d) throws SQLException {
        String kind = (d instanceof SwimmingDuck) ? "SWIMMING"
                : (d instanceof FlyingDuck)   ? "FLYING"
                : "HYBRID";
        try (var ps = con.prepareStatement("""
            UPDATE public."Ducks"
               SET viteza=?, rezistenta=?, tip_rata=?
             WHERE "idDuck"=?
        """)) {
            ps.setObject(1, d.getViteza(), Types.DOUBLE);
            ps.setObject(2, d.getRezistenta(), Types.DOUBLE);
            ps.setString(3, kind);
            ps.setLong(4, d.getId());
            int n = ps.executeUpdate();
            if (n == 0) insertDuck(con, d);
        }
    }

    // ---------- reads ----------
    private static final String BASE_SELECT = """
        SELECT
            u."idUser",
            u.username,
            u.email,
            u.password,
            p.nume,
            p.prenume,
            p."dataNasterii",
            p.ocupatie,
            d.viteza,
            d.rezistenta,
            d.tip_rata
        FROM public."Users" u
        LEFT JOIN public."People" p ON p."idPersoana" = u."idUser"
        LEFT JOIN public."Ducks"  d ON d."idDuck"     = u."idUser"
    """;

    @Override
    public User findById(long id) {
        String sql = BASE_SELECT + " WHERE u.\"idUser\" = ?";
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            try (var rs = ps.executeQuery()) {
                if (!rs.next()) throw new NotFoundException("user", "user not found.");
                return mapRow(rs);
            }
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public User findByUsername(String username) {
        String sql = BASE_SELECT + " WHERE u.username = ?";
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setString(1, username);
            try (var rs = ps.executeQuery()) {
                if (!rs.next()) throw new NotFoundException("user", "user not found.");
                return mapRow(rs);
            }
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public User findByEmail(String email) {
        String sql = BASE_SELECT + " WHERE u.email = ?";
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setString(1, email);
            try (var rs = ps.executeQuery()) {
                if (!rs.next()) throw new NotFoundException("user", "user not found.");
                return mapRow(rs);
            }
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public List<User> getAll() {
        try (var con = db.connect(); var st = con.createStatement(); var rs = st.executeQuery(BASE_SELECT)) {
            var list = new ArrayList<User>();
            while (rs.next()) list.add(mapRow(rs));
            return list;
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public boolean existsById(long id) {
        String sql = "SELECT 1 FROM public.\"Users\" WHERE \"idUser\" = ?";
        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            try (var rs = ps.executeQuery()) { return rs.next(); }
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    // ---------- writes ----------
    @Override
    public void add(User u) {
        try (var con = db.connect()) {
            con.setAutoCommit(false);
            try {
                insertUser(con, u);
                if (u instanceof Person p) insertPerson(con, p);
                else if (u instanceof Duck d) insertDuck(con, d);
                con.commit();
            } catch (SQLException ex) {
                con.rollback();
                if ("23505".equals(ex.getSQLState()))
                    throw new DuplicateException("unique", "id/username/email already exists.");
                throw ex;
            } finally { con.setAutoCommit(true); }
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public void update(User u) {
        try (var con = db.connect()) {
            con.setAutoCommit(false);
            try {
                updateUser(con, u);
                if (u instanceof Person p) upsertPerson(con, p);
                else if (u instanceof Duck d) upsertDuck(con, d);
                con.commit();
            } catch (SQLException ex) {
                con.rollback();
                throw ex;
            } finally { con.setAutoCommit(true); }
        } catch (SQLException e) { throw new RuntimeException(e); }
    }

    @Override
    public void deleteById(long id) {
        try (var con = db.connect();
             var ps = con.prepareStatement("DELETE FROM public.\"Users\" WHERE \"idUser\" = ?")) {
            ps.setLong(1, id);
            int n = ps.executeUpdate();
            if (n == 0) throw new NotFoundException("user", "user does not exist.");
        } catch (SQLException e) { throw new RuntimeException(e); }
    }
}
