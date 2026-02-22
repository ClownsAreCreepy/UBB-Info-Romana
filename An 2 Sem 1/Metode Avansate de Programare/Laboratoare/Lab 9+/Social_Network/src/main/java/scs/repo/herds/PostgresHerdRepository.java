package scs.repo.herds;

import scs.domain.group.Herd;
import scs.domain.user.Duck;
import scs.domain.user.User;
import scs.repo.users.PostgresUserRepository;
import scs.repo.users.UserRepository;
import scs.utilities.database.Db;
import scs.utilities.errors.*;

import java.sql.*;
import java.util.*;

public class PostgresHerdRepository implements HerdRepository<Duck> {
    private final UserRepository userRepo;

    public PostgresHerdRepository(UserRepository userRepo) {
        this.userRepo = userRepo;
    }

    // HELPERS
    private Herd<Duck> mapHerd(ResultSet rs) throws SQLException {
        Long id = rs.getLong("idHerd");
        String name = rs.getString("herdName");
        return new Herd<>(id, name);
    }

    private void loadMembers(Herd<Duck> herd, Connection con) throws SQLException {
        String sql = """
                SELECT 
                    u."idUser", u.username, u.email, u.password,
                    p.name, p.firstName, p."birthDate", p.occupation,
                    d.speed, d.resistance, d.duck_type
                FROM public."HerdMembers" hm
                JOIN public."Users" u ON hm.id_duck = u."idUser"
                LEFT JOIN public."People" p ON u."idUser" = p."idPerson"
                LEFT JOIN public."Ducks" d ON u."idUser" = d."idDuck"
                WHERE hm.id_herd = ?    
                """;
        try (PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, herd.getId());
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    User d = PostgresUserRepository.mapRow(rs);
                    if (d instanceof Duck duck)
                        herd.addDuck(duck);
                }
            }
        }
    }

    private void loadMembersForMultipleHerds(List<Herd<Duck>> herds, Connection con) throws SQLException {
        if (herds.isEmpty())
            return;

        Map<Long, Herd<Duck>> herdMap = new HashMap<>();
        for (Herd<Duck> h : herds)
            herdMap.put(h.getId(), h);

        String placeholders = String.join(",", Collections.nCopies(herds.size(), "?"));

        String sql = """
                SELECT hm.id_herd,
                u."idUser", u.username, u.email, u.password,
                p.name, p.firstName, p."birthDate", p.occupation,
                d.speed, d.resistance, d.duck_type
                FROM public."HerdMembers" hm
                JOIN public."Users" u ON hm.id_duck = u."idUser"
                LEFT JOIN public."People" p ON u."idUser" = p."idPerson"
                LEFT JOIN public."Ducks" d ON u."idUser" = d."idDuck"
                WHERE hm.id_herd IN (%s)
                """.formatted(placeholders);

        try (PreparedStatement ps = con.prepareStatement(sql)) {
            int idx = 1;
            for (Herd<Duck> h : herds)
                ps.setLong(idx++, h.getId());

            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    long herdId = rs.getLong("id_herd");
                    User user = PostgresUserRepository.mapRow(rs);
                    if (user instanceof Duck duck) {
                        Herd<Duck> h = herdMap.get(herdId);
                        if (h != null)
                            h.addDuck(duck);
                    }
                }
            }
        }
    }

    @Override
    public void add(Herd<Duck> herd) {
        String sql = """
                INSERT INTO public."Herds"("herdName")
                VALUES(?)
                RETURNING "idHerd"
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, herd.getName());

            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next())
                    herd.setId(rs.getLong("idHerd"));
            }

        } catch (SQLException e) {
            if ("23505".equals(e.getSQLState()))
                throw new DuplicateException("herd", "herd name already exists.");
            throw new DatabaseException("add herd", e.getMessage());
        }
    }

    public void addDuck(Long herdId, Long duckId) {
        String sql = """
                INSERT INTO public."HerdMembers"(id_herd, id_duck)
                VALUES(?, ?)
                ON CONFLICT DO NOTHING
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, herdId);
            ps.setLong(2, duckId);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new DatabaseException("add herd member", e.getMessage());
        }
    }

    @Override
    public void update(Herd<Duck> herd) {
        String sql = """
                UPDATE public."Herds"
                SET herdName = ?
                WHERE "idHerd" = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, herd.getName());
            ps.setLong(2, herd.getId());

            if (ps.executeUpdate() == 0)
                throw new NotFoundException("herd", "herd not found.");

        } catch (SQLException e) {
            throw new DatabaseException("update herd", e.getMessage());
        }
    }

    @Override
    public Herd<Duck> findById(Long id) {
        String sql = """
                SELECT * FROM public."Herds"
                WHERE "idHerd" = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);

            try (ResultSet rs = ps.executeQuery()) {
                if (!rs.next())
                    throw new NotFoundException("herd", "herd not found.");

                Herd<Duck> herd = mapHerd(rs);
                loadMembers(herd, con);
                return herd;
            }
        } catch (SQLException e) {
            throw new DatabaseException("find herd", e.getMessage());
        }
    }

    @Override
    public Herd<Duck> findByName(String name) {
        String sql = """
                SELECT * FROM public."Herds"
                WHERE herdName = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, name);

            try (ResultSet rs = ps.executeQuery()) {
                if (!rs.next())
                    throw new NotFoundException("herd", "herd " + name + " not found.");

                var herd = mapHerd(rs);
                loadMembers(herd, con);
                return herd;
            }
        } catch (SQLException e) {
            throw new DatabaseException("find herd by name", e.getMessage());
        }
    }

    @Override
    public List<Herd<Duck>> getAll() {
        String sql = """
                SELECT * FROM public."Herds"
                """;

        try (Connection con = Db.getConnection(); Statement st = con.createStatement(); ResultSet rs = st.executeQuery(sql)) {
            List<Herd<Duck>> list = new ArrayList<>();
            while (rs.next())
                list.add(mapHerd(rs));

            loadMembersForMultipleHerds(list, con);

            return list;
        } catch (SQLException e) {
            throw new DatabaseException("get all herds", e.getMessage());
        }
    }

    @Override
    public void deleteById(Long id) {
        String sql = """
                DELETE FROM  public."Herds"
                WHERE "idHerd" = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            if (ps.executeUpdate() == 0)
                throw new NotFoundException("herd", "herd not found.");
        } catch (SQLException e) {
            throw new DatabaseException("delete herd", e.getMessage());
        }
    }

    public void removeDuck(Long herdId, Long duckId) {
        String sql = """
                DELETE FROM public."HerdMembers"
                WHERE id_herd = ? AND id_duck = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, herdId);
            ps.setLong(2, duckId);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new DatabaseException("remove herd member", e.getMessage());
        }
    }

    @Override
    public boolean existsById(Long id) {
        String sql = """
                SELECT 1 FROM public."Herds"
                WHERE "idHerd" = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            throw new DatabaseException("exists herd", e.getMessage());
        }
    }

    @Override
    public boolean existsByName(String name) {
        String sql = """
                SELECT 1 FROM public."Herds"
                WHERE herdName = ?
                """;

        try (Connection con = Db.getConnection(); PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, name);
            try (ResultSet rs = ps.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            throw new DatabaseException("exists herd name", e.getMessage());
        }
    }
}
