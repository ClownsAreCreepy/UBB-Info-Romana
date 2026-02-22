package scs.ui;

import javafx.animation.FadeTransition;
import javafx.animation.PauseTransition;
import javafx.animation.SequentialTransition;
import javafx.application.Platform;
import javafx.scene.control.Label;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.util.Duration;
import scs.app.AppContext;

import javafx.fxml.FXML;
import scs.domain.interactions.FriendRequest;
import scs.domain.interactions.Message;
import scs.domain.user.User;
import scs.service.friend.RequestService;
import scs.service.social.MessageService;
import scs.service.social.UserService;
import scs.ui.controllers.race.EventController;
import scs.ui.controllers.race.HerdController;
import scs.ui.controllers.race.RaceController;
import scs.ui.controllers.social.ChatController;
import scs.ui.controllers.social.UserController;
import scs.ui.controllers.social.SocialController;
import scs.ui.pages.ProfilePage;
import scs.utilities.events.ChangeEventType;
import scs.utilities.events.EntityChangeEvent;


public class MainController {
    @FXML
    private UserController userViewController;
    @FXML
    private SocialController socialViewController;
    @FXML private HerdController herdViewController;
    @FXML private EventController eventViewController;
    @FXML private RaceController raceViewController;
    @FXML
    private ChatController chatViewController;

    @FXML
    private Label notificationLabel;

    @FXML
    private TabPane mainTabPane;

    private RequestService requestService;
    private MessageService messageService;
    private User loggedInUser;

    public void setContext(AppContext ctx, User user, Runnable logoutAction) {
        this.loggedInUser = user;
        this.requestService = ctx.PGRequestService;
        this.messageService = ctx.PGMessageService;

        ProfilePage profilePage = new ProfilePage(user, true, false, ctx.PGUserService, logoutAction);

        Tab profileTab = new Tab("Profile");
        profileTab.setContent(profilePage.getView());
        profileTab.setClosable(false);

        mainTabPane.getTabs().addFirst(profileTab);

        userViewController.setContext(
                ctx.PGUserService,
                ctx.PGRequestService,
                ctx.PGFriendshipService,
                loggedInUser);

        socialViewController.setServices(
                ctx.PGUserService,
                ctx.PGFriendshipService,
                ctx.PGCommunityService,
                ctx.PGRequestService,
                loggedInUser);

        herdViewController.setService(ctx.PGCardService, loggedInUser);

        eventViewController.setServices(ctx.PGEventService, ctx.PGUserService, loggedInUser);

        raceViewController.setServices(ctx.PGCardService, ctx.PGEventService, loggedInUser);

        chatViewController.setServices(ctx.PGMessageService, ctx.PGUserService, ctx.PGFriendshipService);
        chatViewController.setLoggedInUser(user);

        this.requestService.addObserver(this::onFriendRequestEvent);
        this.messageService.addObserver(this::onMessageEvent);
    }

    private void onFriendRequestEvent(EntityChangeEvent<FriendRequest> event) {
        if (event.type() != ChangeEventType.ADD)
            return;

        FriendRequest req = event.data();

        if (req.getTo().getId().equals(loggedInUser.getId())) {
            String senderName = req.getFrom().getUsername();
            Platform.runLater(() -> showNotification("New Friend Request from " + senderName));
        }
    }

    private void onMessageEvent(EntityChangeEvent<Message> event) {
        if (event.type() != ChangeEventType.ADD)
            return;

        Message msg = event.data();

        boolean isForMe = msg.getTo().stream()
                .anyMatch(u -> u.getId().equals(loggedInUser.getId()));

        if (isForMe && msg.getFrom().getId().equals(UserService.RACE_BOT_ID)) {
            String sender = msg.getFrom().getUsername();
            String preview = msg.getText().length() > 50
                    ? msg.getText().substring(0, 50) + "..."
                    : msg.getText();

            Platform.runLater(() -> showNotification(sender + ":\n" + preview));
        }
    }

    private void showNotification(String message) {
        notificationLabel.setText(message);
        notificationLabel.setOpacity(0);
        notificationLabel.setVisible(true);
        notificationLabel.toFront();

        // Fade in
        FadeTransition fadeIn = new FadeTransition(Duration.millis(300), notificationLabel);
        fadeIn.setFromValue(0);
        fadeIn.setToValue(1.0);

        // Stay Visible
        PauseTransition stay = new PauseTransition(Duration.seconds(4));

        // Fade out
        FadeTransition fadeOut = new FadeTransition(Duration.millis(500), notificationLabel);
        fadeOut.setFromValue(1.0);
        fadeOut.setToValue(0);

        // Chain
        SequentialTransition seq = new SequentialTransition(fadeIn, stay, fadeOut);
        seq.setOnFinished(e -> notificationLabel.setVisible(false));
        seq.play();
    }

    public void cleanup() {
        if (userViewController != null) userViewController.cleanup();
        if (chatViewController != null) chatViewController.cleanup();
        if (socialViewController != null) socialViewController.cleanup();
        if (eventViewController != null) eventViewController.cleanup();
        if (herdViewController != null) herdViewController.cleanup();
        if (raceViewController != null) raceViewController.cleanup();

        if (requestService != null) requestService.removeObserver(this::onFriendRequestEvent);
        if (messageService != null) messageService.removeObserver(this::onMessageEvent);
    }
}
