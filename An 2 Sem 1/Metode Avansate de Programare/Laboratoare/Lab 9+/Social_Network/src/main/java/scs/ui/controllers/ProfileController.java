package scs.ui.controllers;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;
import scs.domain.user.*;
import scs.service.social.UserService;
import scs.ui.controllers.logins.LoginController;

import java.io.IOException;
import java.util.Optional;

public class ProfileController {
    @FXML
    private Label initialsLabel;
    @FXML
    private Circle avatarCircle;
    @FXML
    private Label usernameLabel;
    @FXML
    private Label typeBadge;
    @FXML
    private GridPane vitalsGrid;
    @FXML
    private Label emailLabel;
    @FXML
    private Label relationBadge;
    @FXML
    private HBox accountActionsBox;
    @FXML
    private Button btnLogout;
    @FXML
    private Button btnDelete;


    private User currentUser;
    private UserService userService;
    private Runnable logoutHandler;

    public void setContext(User user, UserService service, Runnable logoutHandler) {
        this.currentUser = user;
        this.userService = service;
        this.logoutHandler = logoutHandler;
        updateUI();
    }

    public void updateUI() {
        if (currentUser == null)
            return;

        usernameLabel.setText(currentUser.getUsername());
        emailLabel.setText(currentUser.getEmail());

        setAvatar(currentUser);

        vitalsGrid.getChildren().clear();

        if (currentUser instanceof Person p)
            setupPersonUi(p);
        else if (currentUser instanceof Duck d)
            setupDuckUI(d);
    }

    private void setupPersonUi(Person p) {
        typeBadge.setText("\uD83D\uDC64 PERSON"); // 👤
        typeBadge.setStyle("-fx-background-color: #3498db; -fx-text-fill: white; -fx-padding: 5 15; -fx-background-radius: 20; -fx-font-weight: bold;");

        addVitalRow(0, "Full Name", p.getFullName());
        addVitalRow(1, "Occupation", p.getOccupation());
        addVitalRow(2, "Age", p.getAge() + " years old");
    }

    private void setupDuckUI(Duck d) {
        String badgeText = "\uD83E\uDD86 DUCK"; // 🦆
        String color = "#27ae60";

        if (d instanceof FlyingDuck) {
            badgeText += " (FLYING)";
            color = "#e67e22";
        } else if (d instanceof SwimmingDuck) {
            badgeText += " (SWIMMING)";
            color = "#2980b9";
        } else if (d instanceof HybridDuck) {
            badgeText += " (HYBRID";
            color = "#8e44ad";
        }

        typeBadge.setText(badgeText);
        typeBadge.setStyle("-fx-background-color: " + color + "; -fx-text-fill: white; -fx-padding: 5 15; -fx-background-radius: 20; -fx-font-weight: bold;");

        addVitalRow(0, "Speed", String.format("%.1f km/h", d.getSpeed()));
        addVitalRow(1, "Resistance", String.format("%.1f", d.getResistance()));
    }

    private void addVitalRow(int row, String labelText, String valueText) {
        Label label = new Label(labelText + ":");
        label.setStyle("-fx-font-weight: bold; -fx-text-fill: #7f8c8d");

        Label value = new Label(valueText);
        value.setStyle("-fx-text-fill: #2c3e50; -fx-font-size: 14px;");

        vitalsGrid.add(label, 0, row);
        vitalsGrid.add(value, 1, row);
    }

    private void setAvatar(User user) {
        String name = user.getUsername();
        if (name != null && !name.isEmpty())
            initialsLabel.setText(name.substring(0, 1).toUpperCase());

        String colorHex = "#95a5a6";

        if (user instanceof Person)
            colorHex = "#3498db";
        else if (user instanceof Duck d)
            if (d instanceof FlyingDuck)
                colorHex = "#e67e22";
            else if (d instanceof SwimmingDuck)
                colorHex = "#2980b9";
            else if (d instanceof HybridDuck)
                colorHex = "#8e44ad";
            else
                colorHex = "#27ae60";

        avatarCircle.setFill(Color.web(colorHex));
    }

    public void setRelationStatus(boolean isMe, boolean isFriend) {
        if (isMe) {
            relationBadge.setVisible(false);
            relationBadge.setManaged(false);

            if (accountActionsBox != null) {
                accountActionsBox.setVisible(true);
                accountActionsBox.setManaged(true);
            }

//            relationBadge.setText("IT'S YOU");
//            relationBadge.setStyle("-fx-text-fill: #7f8c8d; -fx-border-color: #7f8c8d; -fx-border-radius: 10; -fx-padding: 3 8;");
//            relationBadge.setVisible(true);
//            relationBadge.setVisible(true);
        } else {
            if (accountActionsBox != null) {
                accountActionsBox.setVisible(false);
                accountActionsBox.setManaged(false);
            }

            relationBadge.setVisible(true);
            relationBadge.setManaged(true);

            if (isFriend) {
                relationBadge.setText("FRIEND");
                relationBadge.setStyle("-fx-text-fill: #27ae60; -fx-border-color: #27ae60; -fx-border-radius: 10; -fx-padding: 3 8;");
            } else {
                relationBadge.setText("STRANGER");
                relationBadge.setStyle("-fx-text-fill: #e67e22; -fx-border-color: #e67e22; -fx-border-radius: 10; -fx-padding: 3 8;");
            }
        }
    }

    @FXML public void onLogout() {
        if (confirmAction("Log Out", "Are you sure you want to log out?"))
            if (logoutHandler != null)
                logoutHandler.run();
    }

    @FXML public void onDeleteAccount() {
        if (confirmAction("Delete Account", "WARNING: This cannot be undone. Are you sure?")) {
            try {
                userService.deleteUser(currentUser.getId());
                if (logoutHandler != null)
                    logoutHandler.run();
            } catch (Exception e) {
                new Alert(Alert.AlertType.ERROR, "Could not delete accound: " + e.getMessage()).show();
            }
        }
    }

    private boolean confirmAction(String title, String content) {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);

        Optional<ButtonType> result = alert.showAndWait();
        return result.isPresent() && result.get() == ButtonType.OK;
    }
}
