package app;

import domain.user.Duck;
import repo.FriendshipRepository;
import repo.herds.CardRepository;
import repo.herds.InMemoryCardRepository;
import repo.users.InMemoryUserRepository;
import repo.users.UserRepository;
import service.*;
import utilities.IdGenerator;

public class AppContext {
    public final UserRepository userRepo = new InMemoryUserRepository();

    public final CardRepository<Duck> cardRepo = new InMemoryCardRepository<>();

    public final FriendshipRepository graph = new FriendshipRepository();

    public final UserService userService = new UserService(userRepo);
    public final FriendshipService friendshipService = new FriendshipService(userRepo, graph);
    public final CommunityService communityService = new CommunityService(userRepo, graph);
    public final CardService cardService = new CardService(cardRepo);

}
