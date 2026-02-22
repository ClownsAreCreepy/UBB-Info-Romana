package scs.app;

import scs.domain.user.Duck;
import scs.repo.events.EventRepository;
import scs.repo.events.PostgresEventRepository;
import scs.repo.friend.friendships.FriendshipRepository;
//import scs.repo.friend.friendships.InMemoryFriendshipRepository;
import scs.repo.friend.friendships.PostgresFriendshipRepository;
import scs.repo.friend.requests.PostgresRequestRepository;
import scs.repo.friend.requests.RequestRepository;
import scs.repo.herds.HerdRepository;
//import scs.repo.herds.InMemoryCardRepository;
import scs.repo.herds.PostgresHerdRepository;
//import scs.repo.users.InMemoryUserRepository;
import scs.repo.messages.MessageRepository;
import scs.repo.messages.PostgresMessageRepository;
import scs.repo.users.PostgresUserRepository;
import scs.repo.users.UserRepository;
import scs.service.*;
import scs.service.friend.CommunityService;
import scs.service.friend.FriendshipService;
import scs.service.friend.RequestService;
import scs.service.social.MessageService;
import scs.service.social.UserService;
import scs.utilities.IdGenerator;
import scs.utilities.database.Db;
import scs.utilities.errors.DatabaseException;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;

public class AppContext {
    static {
        String dbUrl = System.getenv("DB_URL");
        String dbUser = System.getenv("DB_USER");
        String dbPass = System.getenv("DB_PASSWORD");

        Db.setGlobalConnection(dbUrl, dbUser, dbPass);
    }

    private final IdGenerator ids;

    {
        ids = new IdGenerator();
        ids.bumpToAtLeast(fetchMaxUserId() + 1);
    }

    // id sync
    private long fetchMaxUserId() {
        String sql = "SELECT COALESCE(MAX(\"idUser\"), 0) AS max_id FROM public.\"Users\"";
        try (Connection con = Db.getConnection(); Statement st = con.createStatement(); ResultSet rs = st.executeQuery(sql)) {
            rs.next();
            return rs.getLong("max_id");
        } catch (Exception e) {
            throw new DatabaseException("max id", e.getMessage());
        }
    }


    //public final UserRepository MemUserRepo = new InMemoryUserRepository();
    public final UserRepository PGUserRepo = new PostgresUserRepository();

    //public final CardRepository<Duck> MemCardRepo = new InMemoryCardRepository<>();
    public final HerdRepository<Duck> PGCardRepo = new PostgresHerdRepository(PGUserRepo);

    //public final FriendshipRepository MemFriendRepo = new InMemoryFriendshipRepository();
    public final FriendshipRepository PGFriendRepo = new PostgresFriendshipRepository();

    public final EventRepository PGEventRepo = new PostgresEventRepository();

    public final MessageRepository PGMessageRepo = new PostgresMessageRepository(PGUserRepo);

    public final RequestRepository PGRequestRepo = new PostgresRequestRepository(PGUserRepo);


    //public final UserService MemUserService = new UserService(MemUserRepo, ids);
    public final UserService PGUserService = new UserService(PGUserRepo, ids);

    //public final FriendshipService MemFriendshipService = new FriendshipService(MemUserRepo, MemFriendRepo);
    public final FriendshipService PGFriendshipService = new FriendshipService(PGUserRepo, PGFriendRepo);

    //public final CommunityService MemCommunityService = new CommunityService(MemUserRepo, MemFriendRepo);
    public final CommunityService PGCommunityService = new CommunityService(PGUserRepo, PGFriendRepo);

    //public final CardService MemCardService = new CardService(MemCardRepo);
    public final HerdService PGCardService = new HerdService(PGCardRepo);

    public final MessageService PGMessageService = new MessageService(PGMessageRepo, PGUserRepo);

    public final EventService PGEventService = new EventService(PGEventRepo, PGUserRepo, PGMessageService);

    public final RequestService PGRequestService = new RequestService(PGRequestRepo, PGFriendshipService, PGUserRepo);

}
