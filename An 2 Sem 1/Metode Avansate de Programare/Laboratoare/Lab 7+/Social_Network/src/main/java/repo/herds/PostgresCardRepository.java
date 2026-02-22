package repo.herds;

import domain.group.Card;
import domain.user.Duck;
import repo.users.UserRepository;
import utilities.database.Db;
import utilities.errors.*;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class PostgresCardRepository implements CardRepository<Duck> {
    private final Db db;
    private final UserRepository userRepo;

    public PostgresCardRepository(Db db, UserRepository userRepo) {
        this.db = db;
        this.userRepo = userRepo;
    }

    // HELPERS
    private Card<Duck> mapCard(ResultSet rs) throws SQLException {
        long id = rs.getLong("idCard");
        String nume = rs.getString("nume_card");
        return new Card<>(id, nume);
    }

    private void loadMembers(Card<Duck> card, Connection con) throws SQLException {
        try (var ps = con.prepareStatement("""
                SELECT id_duck FROM public."CardMembers"
                WHERE id_card = ?
                """)) {
            ps.setLong(1, card.getId());
            try (var rs = ps.executeQuery()) {
                while (rs.next()) {
                    long duckId = rs.getLong("id_duck");
                    var d = userRepo.findById(duckId);
                    if (d instanceof Duck duck)
                        card.addDuck(duck);
                }
            }
        }
    }

    @Override
    public void add(Card<Duck> card) {
        String sql = """
                INSERT INTO public."Cards"( nume_card)
                VALUES(?)
                RETURNING "idCard"
                """;

        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setString(1, card.getNumeCard());

            try (var rs = ps.executeQuery()) {
                if (rs.next()) {
                    long newId = rs.getLong("idCard");
                    card.setId(newId);
                }
            }

        } catch (SQLException e) {
            if ("23505".equals(e.getSQLState()))
                throw new DuplicateException("card name", "herd name already exists.");
            throw new RuntimeException(e);
        }
    }

    public void addDuck(long cardId, long duckId) {
        String sql = """
                INSERT INTO public."CardMembers"(id_card, id_duck)
                VALUES(?, ?)
                ON CONFLICT DO NOTHING
                """;

        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, cardId);
            ps.setLong(2, duckId);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void update(Card<Duck> card) {
        String sql = """
                UPDATE public."Cards"
                SET nume_card = ?
                WHERE "idCard" = ?
                """;

        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setString(1, card.getNumeCard());
            ps.setLong(2, card.getId());

            if (ps.executeUpdate() == 0)
                throw new NotFoundException("card", "herd not found.");

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Card<Duck> findById(long id) {
        String sql = """
                SELECT * FROM public."Cards"
                WHERE "idCard" = ?
                """;

        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);

            try (var rs = ps.executeQuery()) {
                if (!rs.next())
                    throw new NotFoundException("card", "herd not found.");

                var card = mapCard(rs);
                loadMembers(card, con);
                return card;
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Card<Duck> findByName(String name) {
        String sql = """
                SELECT * FROM public."Cards"
                WHERE nume_card = ?
                """;

        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setString(1, name);

            try (var rs = ps.executeQuery()) {
                if (!rs.next())
                    throw new NotFoundException("card", "herd not found.");

                var card = mapCard(rs);
                loadMembers(card, con);
                return card;
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public List<Card<Duck>> getAll() {
        String sql = """
                SELECT * FROM public."Cards"
                """;

        try (var con = db.connect(); var st = con.createStatement(); var rs = st.executeQuery(sql)) {
            var list = new ArrayList<Card<Duck>>();

            while (rs.next()) {
                var c = mapCard(rs);
                loadMembers(c, con);
                list.add(c);
            }

            return list;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void deleteById(long id) {
        String sql = """
                DELETE FROM  public."Cards"
                WHERE "idCard" = ?
                """;

        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            if (ps.executeUpdate() == 0)
                throw new NotFoundException("card", "herd not found.");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void removeDuck(long cardId, long duckId) {
        String sql = """
                DELETE FROM public."CardMembers"
                WHERE id_card = ? AND id_duck = ?
                """;

        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, cardId);
            ps.setLong(2, duckId);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public boolean existsById(long id) {
        String sql = """
                SELECT 1 FROM public."Cards"
                WHERE "idCard" = ?
                """;

        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setLong(1, id);
            try (var rs = ps.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public boolean existsByName(String name) {
        String sql = """
                SELECT 1 FROM public."Cards"
                WHERE nume_card = ?
                """;

        try (var con = db.connect(); var ps = con.prepareStatement(sql)) {
            ps.setString(1, name);
            try (var rs = ps.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
