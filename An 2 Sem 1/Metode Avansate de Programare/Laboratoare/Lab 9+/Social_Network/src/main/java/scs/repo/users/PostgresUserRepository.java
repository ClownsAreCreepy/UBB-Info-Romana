package scs.repo.users;

import scs.domain.user.*;
import scs.utilities.database.Db;
import scs.utilities.errors.DuplicateException;
import scs.utilities.errors.NotFoundException;
import scs.utilities.errors.DatabaseException;
import scs.utilities.paging.Page;
import scs.utilities.paging.Pageable;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class PostgresUserRepository implements UserRepository {
    public PostgresUserRepository() {
    }

    private static final String BASE_SELECT = """
            SELECT
                u."idUser", u.username, u.email, u.password,
                p.name, p.firstName, p."birthDate", p.occupation,
                d.speed, d.resistance, d.duck_type
            FROM public."Users" u
            LEFT JOIN public."People" p ON p."idPerson" = u."idUser"
            LEFT JOIN public."Ducks" d ON d."idDuck" = u."idUser"
            """;

    // ---------- mapping ----------
    public static User mapRow(ResultSet rs) throws SQLException {
        Long id = rs.getLong("idUser");
        String username = rs.getString("username");
        String email = rs.getString("email");
        String password = rs.getString("password");     // hash

        // People
        String name = rs.getString("name");
        String firstName = rs.getString("firstName");
        Date birthDate = rs.getDate("birthDate");
        String occupation = rs.getString("occupation");

        // Ducks (nullable)
        Double speed = rs.getObject("speed", Double.class);
        Double resistance = rs.getObject("resistance", Double.class);
        String duckType = rs.getString("duck_type");

        boolean isPerson = (name != null);
        boolean isDuck = (duckType != null);

        if (isPerson) {
            LocalDate birth = (birthDate == null ? null : birthDate.toLocalDate());
            return new Person.Builder(id)
                    .username(username)
                    .email(email)
                    .password(password)
                    .name(name)
                    .firstName(firstName)
                    .birthDate(birth)
                    .occupation(occupation)
                    .build();
        }

        if (isDuck) {
            double s = (speed == null ? 0.0 : speed);
            double r = (resistance == null ? 0.0 : resistance);
            return switch (duckType) {
                case "SWIMMING" -> new SwimmingDuck(id, username, email, password, s, r);
                case "FLYING" -> new FlyingDuck(id, username, email, password, s, r);
                case "HYBRID" -> new HybridDuck(id, username, email, password, s, r);
                default -> throw new DatabaseException("mapping", "Unknown duck type: " + duckType);
            };
        }

        // default bare Person
        throw new DatabaseException("mapping", "User " + id + " is neither Person nor Duck");
    }

    // ---------- insert/update helpers ----------
    private void insertUser(Connection con, User u) throws SQLException {
        try (PreparedStatement ps = con.prepareStatement("""
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
        try (PreparedStatement ps = con.prepareStatement("""
                    INSERT INTO public."People"("idPerson", name, firstName, "birthDate", occupation)
                    VALUES (?, ?, ?, ?, ?)
                """)) {
            ps.setLong(1, p.getId());
            ps.setString(2, p.getName());
            ps.setString(3, p.getFirstName());
            ps.setObject(4, p.getBirthDate());
            ps.setString(5, p.getOccupation());
            ps.executeUpdate();
        }
    }

    private static void insertDuck(Connection con, Duck d) throws SQLException {
        String kind = (d instanceof SwimmingDuck) ? "SWIMMING"
                : (d instanceof FlyingDuck) ? "FLYING"
                : (d instanceof HybridDuck) ? "HYBRID" : null;

        try (PreparedStatement ps = con.prepareStatement("""
                    INSERT INTO public."Ducks"("idDuck", speed, resistance, duck_type)
                    VALUES (?, ?, ?, ?)
                """)) {
            ps.setLong(1, d.getId());
            ps.setObject(2, d.getSpeed());
            ps.setObject(3, d.getResistance());
            ps.setString(4, kind);
            ps.executeUpdate();
        }
    }

    private boolean updateUser(Connection con, User u) throws SQLException {
        try (PreparedStatement ps = con.prepareStatement("""
                    UPDATE public."Users"
                       SET username=?, email=?, password=?
                     WHERE "idUser"=?
                """)) {
            ps.setString(1, u.getUsername());
            ps.setString(2, u.getEmail());
            ps.setString(3, u.getPassword());
            ps.setLong(4, u.getId());
            return ps.executeUpdate() > 0;
        }
    }

    private static void upsertPerson(Connection con, Person p) throws SQLException {
        try (PreparedStatement ps = con.prepareStatement("""
                    UPDATE public."People"
                       SET name=?, firstName=?, "birthDate"=?, occupation=?
                     WHERE "idPerson"=?
                """)) {
            ps.setString(1, p.getName());
            ps.setString(2, p.getFirstName());
            ps.setObject(3, p.getBirthDate());
            ps.setString(4, p.getOccupation());
            ps.setLong(5, p.getId());
            if (ps.executeUpdate() == 0) insertPerson(con, p);
        }
    }

    private static void upsertDuck(Connection con, Duck d) throws SQLException {
        String kind = (d instanceof SwimmingDuck) ? "SWIMMING"
                : (d instanceof FlyingDuck) ? "FLYING"
                : "HYBRID";
        try (PreparedStatement ps = con.prepareStatement("""
                    UPDATE public."Ducks"
                       SET speed=?, resistance=?, duck_type=?
                     WHERE "idDuck"=?
                """)) {
            ps.setObject(1, d.getSpeed());
            ps.setObject(2, d.getResistance());
            ps.setString(3, kind);
            ps.setLong(4, d.getId());
            if (ps.executeUpdate() == 0) insertDuck(con, d);
        }
    }

    // ---------- reads ----------
    @Override
    public User findById(Long id) {
        String sql = BASE_SELECT + " WHERE u.\"idUser\" = ?";
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if (!rs.next()) throw new NotFoundException("user", "user with id " + id + " not found.");
                return mapRow(rs);
            }
        } catch (SQLException e) {
            throw new DatabaseException("read", e.getMessage());
        }
    }

    @Override
    public User findByUsername(String username) {
        String sql = BASE_SELECT + " WHERE u.username = ?";
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, username);
            try (ResultSet rs = ps.executeQuery()) {
                if (!rs.next()) throw new NotFoundException("user", "user " + username + " not found.");
                return mapRow(rs);
            }
        } catch (SQLException e) {
            throw new DatabaseException("read", e.getMessage());
        }
    }

    @Override
    public User findByEmail(String email) {
        String sql = BASE_SELECT + " WHERE u.email = ?";
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, email);
            try (ResultSet rs = ps.executeQuery()) {
                if (!rs.next()) throw new NotFoundException("user", "Email " + email + " user not found.");
                return mapRow(rs);
            }
        } catch (SQLException e) {
            throw new DatabaseException("read", e.getMessage());
        }
    }

    @Override
    public List<User> getAll() {
        try (Connection con = Db.getConnection(); Statement st = con.createStatement(); ResultSet rs = st.executeQuery(BASE_SELECT)) {
            List<User> list = new ArrayList<>();
            while (rs.next()) list.add(mapRow(rs));
            return list;
        } catch (SQLException e) {
            throw new DatabaseException("read_all", e.getMessage());
        }
    }

    @Override
    public List<User> findUsersByIds(Collection<Long> ids) {
        if (ids == null || ids.isEmpty())
            return new ArrayList<>();

        String sql = BASE_SELECT + " WHERE u.\"idUser\" = ANY(?)";

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            Array idArray = con.createArrayOf("bigint", ids.toArray());
            ps.setArray(1, idArray);

            List<User> list = new ArrayList<>();
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next())
                    list.add(mapRow(rs));
            }

            return list;
        } catch (SQLException e) {
            throw new DatabaseException("find users", e.getMessage());
        }
    }

    @Override
    public Page<User> search(Pageable pageable, String typeFilter, String duckType, List<Long> includeIds, List<Long> excludeIds) {
        StringBuilder sql = new StringBuilder(BASE_SELECT);
        StringBuilder countSql = new StringBuilder("""
                SELECT COUNT(*) FROM public."Users" u
                LEFT JOIN public."People" p ON p."idPerson" = u."idUser"
                LEFT JOIN public."Ducks" d ON d."idDuck" = u."idUser"
                """);

        List<String> conditions = new ArrayList<>();
        List<Object> params = new ArrayList<>();

        // Type filter
        if (typeFilter.equals("PERSON")) {
            conditions.add("p.\"idPerson\" IS NOT NULL");
        } else if (typeFilter.equals("DUCK")) {
            // Duck filter
            switch (duckType) {
                case "SWIMMING" -> conditions.add("d.duck_type = 'SWIMMING'");
                case "FLYING" -> conditions.add("d.duck_type = 'FLYING'");
                case "HYBRID" -> conditions.add("d.duck_type = 'HYBRID'");
                default -> conditions.add("d.\"idDuck\" IS NOT NULL");
            }
        }

        // Inclusion List
        if (includeIds != null && !includeIds.isEmpty()) {
            conditions.add("u.\"idUser\" = ANY (?)");
            params.add(includeIds.toArray(new Long[0]));
        }

        // Exclusion List
        if (excludeIds != null && !excludeIds.isEmpty()) {
            conditions.add("NOT (u.\"idUser\" = ANY (?))");
            params.add(excludeIds.toArray(new Long[0]));
        }

        // Assemble
        if (!conditions.isEmpty()) {
            String where = "WHERE " + String.join(" AND ", conditions);
            sql.append(where);
            countSql.append(where);
        }

        sql.append(" ORDER BY u.\"idUser\" ASC");

        try (Connection con = Db.getConnection()) {
            long total = 0;
            try (PreparedStatement psCount = con.prepareStatement(countSql.toString())) {
                int idx = 1;
                for (Object p : params)
                    if (p instanceof Long[])
                        psCount.setArray(idx++, con.createArrayOf("bigint", (Long[]) p));
                    else
                        psCount.setObject(idx++, p);

                try (ResultSet rs = psCount.executeQuery()) {
                    if (rs.next())
                        total = rs.getLong(1);
                }
            }

            List<User> users = new ArrayList<>();
            sql.append(" LIMIT ? OFFSET ?");

            try (PreparedStatement ps = con.prepareStatement(sql.toString())) {
                int idx = 1;
                for (Object p : params)
                    if (p instanceof Long[])
                        ps.setArray(idx++, con.createArrayOf("bigint", (Long[]) p));
                    else
                        ps.setObject(idx++, p);

                ps.setInt(idx++, pageable.getPageSize());
                ps.setInt(idx++, pageable.getOffset());

                try (ResultSet rs = ps.executeQuery()) {
                    while (rs.next())
                        users.add(mapRow(rs));
                }
            }

            return new Page<>(users, (int) total, pageable.getPageSize());
        } catch (SQLException e) {
            throw new DatabaseException("search users", e.getMessage());
        }
    }

    @Override
    public boolean existsById(Long id) {
        String sql = "SELECT 1 FROM public.\"Users\" WHERE \"idUser\" = ?";
        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            throw new DatabaseException("exists", e.getMessage());
        }
    }

    // ---------- writes ----------
    @Override
    public void add(User u) {
        try (Connection con = Db.getConnection()) {
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
                throw new DatabaseException("add", ex.getMessage());
            } finally {
                con.setAutoCommit(true);
            }
        } catch (SQLException e) {
            throw new DatabaseException("connection", e.getMessage());
        }
    }

    @Override
    public void update(User u) {
        try (Connection con = Db.getConnection()) {
            con.setAutoCommit(false);
            try {
                if (!updateUser(con, u))
                    throw new DatabaseException("user", "User " + u.getId() + " does not exist.");

                if (u instanceof Person p) upsertPerson(con, p);
                else if (u instanceof Duck d) upsertDuck(con, d);
                con.commit();
            } catch (SQLException ex) {
                con.rollback();
                throw new DatabaseException("update", ex.getMessage());
            } finally {
                con.setAutoCommit(true);
            }
        } catch (SQLException e) {
            throw new DatabaseException("connection", e.getMessage());
        }
    }

    @Override
    public void deleteById(Long id) {
        try (Connection con = Db.getConnection();
             PreparedStatement ps = con.prepareStatement("DELETE FROM public.\"Users\" WHERE \"idUser\" = ?")) {
            ps.setLong(1, id);
            int n = ps.executeUpdate();
            if (n == 0) throw new NotFoundException("user", "User " + id + " does not exist.");
        } catch (SQLException e) {
            throw new DatabaseException("delete", e.getMessage());
        }
    }
}

//    @Override
//    public Page<User> findAll(Pageable pageable) {
//        int limit = pageable.getPageSize();
//        int offset = pageable.getOffset();
//
//        String sqlData = BASE_SELECT + " ORDER BY u.\"idUser\" LIMIT ? OFFSET ?";
//        String sqlCount = "SELECT COUNT(*) FROM public.\"Users\"";
//
//        List<User> usersOnPage = new ArrayList<>();
//        int totalCount = 0;
//
//        try (Connection con = Db.getConnection()) {
//            try (PreparedStatement ps = con.prepareStatement(sqlData)) {
//                ps.setInt(1, limit);
//                ps.setInt(2, offset);
//                try (ResultSet rs = ps.executeQuery()) {
//                    while (rs.next())
//                        usersOnPage.add(mapRow(rs));
//                }
//            }
//
//            try (PreparedStatement ps = con.prepareStatement(sqlCount); ResultSet rs = ps.executeQuery()) {
//                while (rs.next())
//                    totalCount = rs.getInt(1);
//            }
//        } catch (SQLException e) {
//            throw new DatabaseException("find all paginated", e.getMessage());
//        }
//
//        return new Page<>(usersOnPage, totalCount, limit);
//    }
//
//    @Override
//    public Page<Duck> findAllDucks(Pageable pageable, String type) {
//        int limit = pageable.getPageSize();
//        int offset = pageable.getOffset();
//        boolean filterByType = (type != null && !type.equals("ALL"));
//
//        // Build SQL dynamically based on filter
//        StringBuilder whereClause = new StringBuilder(" WHERE d.\"idDuck\" IS NOT NULL");
//        if (filterByType) {
//            whereClause.append(" AND d.duck_type = ? ");
//        }
//
//        String sqlData = BASE_SELECT + whereClause + " ORDER BY u.\"idUser\" LIMIT ? OFFSET ?";
//        String sqlCount = "SELECT COUNT(*) FROM public.\"Users\" u JOIN public.\"Ducks\" d ON u.\"idUser\" = d.\"idDuck\" " + whereClause;
//
//        List<Duck> ducks = new ArrayList<>();
//        int totalCount = 0;
//
//        try (Connection con = Db.getConnection()) {
//            try (PreparedStatement ps = con.prepareStatement(sqlData)) {
//                int paramIndex = 1;
//                if (filterByType) {
//                    ps.setString(paramIndex++, type);
//                }
//
//                ps.setInt(paramIndex++, limit);
//                ps.setInt(paramIndex++, offset);
//
//                try (ResultSet rs = ps.executeQuery()) {
//                    while (rs.next()) {
//                        User u = mapRow(rs);
//                        if (u instanceof Duck d)
//                            ducks.add(d);
//                    }
//                }
//            }
//
//            try (PreparedStatement ps = con.prepareStatement(sqlCount)) {
//                if (filterByType)
//                    ps.setString(1, type);
//
//                try (ResultSet rs = ps.executeQuery()) {
//                    if (rs.next())
//                        totalCount = rs.getInt(1);
//                }
//            }
//        } catch (SQLException e) {
//            throw new DatabaseException("page ducks", e.getMessage());
//        }
//
//        return new Page<>(ducks, totalCount, limit);
//    }
//
//    @Override
//    public Page<Person> findAllPeople(Pageable pageable) {
//        int limit = pageable.getPageSize();
//        int offset = pageable.getOffset();
//
//        String sqlData = BASE_SELECT + """
//                WHERE p."idPerson" IS NOT NULL
//                ORDER BY u."idUser" LIMIT ? OFFSET ?
//                """;
//
//        String sqlCount = "SELECT COUNT(*) FROM public.\"People\"";
//
//        List<Person> people = new ArrayList<>();
//        int totalCount = 0;
//
//        try (Connection con = Db.getConnection()) {
//            try (PreparedStatement ps = con.prepareStatement(sqlData)) {
//                ps.setInt(1, limit);
//                ps.setInt(2, offset);
//                try (ResultSet rs = ps.executeQuery()) {
//                    while (rs.next()) {
//                        User u = mapRow(rs);
//                        if (u instanceof Person p)
//                            people.add(p);
//                    }
//                }
//            }
//
//            try (PreparedStatement ps = con.prepareStatement(sqlCount); ResultSet rs = ps.executeQuery()) {
//                if (rs.next())
//                    totalCount = rs.getInt(1);
//            }
//        } catch (SQLException e) {
//            throw new DatabaseException("find all people", e.getMessage());
//        }
//
//        return new Page<>(people, totalCount, limit);
//    }