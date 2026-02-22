package scs.ui.pages;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import scs.domain.user.User;
import scs.service.social.UserService;
import scs.ui.controllers.ProfileController;

import java.io.IOException;

public class ProfilePage implements Page {
    private Parent view;
    private ProfileController controller;
    private final User targetUser;

    private final UserService userService;
    private final Runnable logoutHandler;

    public ProfilePage(User user, boolean isMe, boolean isFriend, UserService userService, Runnable logoutHandler) {
        this.targetUser = user;
        this.userService = userService;
        this.logoutHandler = logoutHandler;

        loadView(isMe, isFriend);
    }

    private void loadView(boolean isMe, boolean isFriend) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/scs/side-views/profile-view.fxml"));
            this.view = loader.load();
            this.controller = loader.getController();

            if (this.controller != null) {
                this.controller.setContext(targetUser, userService, logoutHandler);
                this.controller.setRelationStatus(isMe, isFriend);
            }
        } catch (IOException e) {
            throw new RuntimeException("Failed to load Profile Page ", e);
        }
    }

    @Override
    public Parent getView() {
        return view;
    }

    @Override
    public void refresh() {
        if (controller != null)
            controller.updateUI();
    }

}
