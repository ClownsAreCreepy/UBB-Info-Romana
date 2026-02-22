package app;

import ui.Console;

public class Main {
    public static void main(String[] args) {
        var ctx = new AppContext();
        var ui = new Console(ctx.userService, ctx.friendshipService, ctx.communityService, ctx.cardService);

        // ctx.friendshipService.syncWithUsers();
        ui.run();
    }
}