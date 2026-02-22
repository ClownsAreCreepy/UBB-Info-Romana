package app;

import ui.Console;

import java.sql.SQLException;

public class Main {
    public static void main(String[] args) {
        var ctx = new AppContext();
//        var MemUi = new Console(ctx.MemUserService, ctx.MemFriendshipService, ctx.MemCommunityService, ctx.cardService);
//        MemUi.populate();

//        MemUi.run();


        var PGUi = new Console(ctx.PGUserService, ctx.PGFriendshipService, ctx.PGCommunityService, ctx.PGCardService, ctx.PGEventService);

        PGUi.run();
    }
}
