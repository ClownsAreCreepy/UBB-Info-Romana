package app;

import domain.user.Duck;
import repo.events.EventRepository;
import repo.events.PostgresEventRepository;
import repo.friendships.FriendshipRepository;
//import repo.friendships.InMemoryFriendshipRepository;
import repo.friendships.PostgresFriendshipRepository;
import repo.herds.CardRepository;
//import repo.herds.InMemoryCardRepository;
import repo.herds.PostgresCardRepository;
//import repo.users.InMemoryUserRepository;
import repo.users.PostgresUserRepository;
import repo.users.UserRepository;
import service.*;
import utilities.IdGenerator;
import utilities.database.Db;

import java.sql.SQLException;

public class AppContext {
    private final Db db = new Db(
            "jdbc:postgresql://localhost:5432/postgres?sslmode=disable",
            "postgres",
            "Wolverine1134"
    );

    //public final UserRepository MemUserRepo = new InMemoryUserRepository();
    public final UserRepository PGUserRepo = new PostgresUserRepository(db);

    //public final CardRepository<Duck> MemCardRepo = new InMemoryCardRepository<>();
    public final CardRepository<Duck> PGCardRepo = new PostgresCardRepository(db, PGUserRepo);

    //public final FriendshipRepository MemFriendRepo = new InMemoryFriendshipRepository();
    public final FriendshipRepository PGFriendRepo = new PostgresFriendshipRepository(db);

    public final EventRepository PGEventRepo = new PostgresEventRepository(db);

    private final IdGenerator ids;

    {
        ids = new IdGenerator();
        ids.bumpToAtLeast(fetchMaxUserId() + 1);
    }

    // id sync
    private long fetchMaxUserId() {
        String sql = "SELECT COALESCE(MAX(\"idUser\"), 0) AS max_id FROM public.\"Users\"";
        try (var con = db.connect(); var st = con.createStatement(); var rs = st.executeQuery(sql)) {
            rs.next();
            return rs.getLong("max_id");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //public final UserService MemUserService = new UserService(MemUserRepo, ids);
    public final UserService PGUserService = new UserService(PGUserRepo, ids);

    //public final FriendshipService MemFriendshipService = new FriendshipService(MemUserRepo, MemFriendRepo);
    public final FriendshipService PGFriendshipService = new FriendshipService(PGUserRepo, PGFriendRepo);

    //public final CommunityService MemCommunityService = new CommunityService(MemUserRepo, MemFriendRepo);
    public final CommunityService PGCommunityService = new CommunityService(PGUserRepo, PGFriendRepo);


    //public final CardService MemCardService = new CardService(MemCardRepo);
    public final CardService PGCardService = new CardService(PGCardRepo);

    public final EventService PGEventService = new EventService(PGEventRepo, PGUserRepo, ids);

}
