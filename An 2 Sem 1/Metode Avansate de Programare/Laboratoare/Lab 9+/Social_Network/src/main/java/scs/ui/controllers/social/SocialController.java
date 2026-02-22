package scs.ui.controllers.social;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.*;
import scs.domain.interactions.FriendRequest;
import scs.domain.interactions.RequestStatus;
import scs.domain.user.User;
import scs.service.friend.CommunityService;
import scs.service.friend.FriendshipService;
import scs.service.social.UserService;

import javafx.fxml.FXML;
import scs.service.friend.RequestService;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observer;

import java.time.format.DateTimeFormatter;
import java.util.List;

public class SocialController implements Observer<EntityChangeEvent<FriendRequest>> {
    @FXML
    private TextArea consoleLog;
    @FXML
    private ListView<FriendRequest> requestsList;

    private final ObservableList<FriendRequest> requestsModel = FXCollections.observableArrayList();

    private UserService users;
    private FriendshipService friends;
    private CommunityService community;
    private RequestService requestService;
    private User currentUser;

    public void setServices(UserService u, FriendshipService f, CommunityService c, RequestService r, User loggedIn) {
        this.users = u;
        this.friends = f;
        this.community = c;
        this.requestService = r;
        this.currentUser = loggedIn;

        this.requestService.addObserver(this);

        initRequestList();
        initialLoad();
        log("Services initialized for " + currentUser.getUsername());
    }

    private void log(String message) {
        Platform.runLater(() -> consoleLog.appendText(message + "\n"));
    }

    @Override
    public void update(EntityChangeEvent<FriendRequest> event) {
        Platform.runLater(() -> {
            FriendRequest req = event.data();

            boolean isForMe = req.getTo().getId().equals(currentUser.getId());
            boolean isFromMe = req.getFrom().getId().equals(currentUser.getId());

            if (!isForMe && !isFromMe)
                return;

            switch (event.type()) {
                case ADD:
                    if (isForMe && req.getStatus() == RequestStatus.PENDING)
                        requestsModel.addFirst(req);
                    break;

                case UPDATE:
                    if (req.getStatus() != RequestStatus.PENDING)
                        requestsModel.remove(req);
                    break;

                case DELETE:
                    requestsModel.remove(req);
                    break;
            }
        });
    }

    private void initRequestList() {
        requestsList.setItems(requestsModel);

        requestsList.setCellFactory(param -> new ListCell<>() {
            @Override
            protected void updateItem(FriendRequest item, boolean empty) {
                super.updateItem(item, empty);
                if (empty || item == null)
                    setText(null);
                else {
                    String from = item.getFrom().getUsername();
                    String date = item.getDate().format(DateTimeFormatter.ofPattern("dd/MM HH:mm"));
                    setText(from + " (" + date + ")");
                }
            }
        });
    }

    private void initialLoad() {
        if (currentUser == null)
            return;

        List<FriendRequest> pending = requestService.getPendingRequests(currentUser.getId());
        requestsModel.setAll(pending);
    }

    @FXML
    public void onAccept() {
        FriendRequest selected = requestsList.getSelectionModel().getSelectedItem();
        if (selected == null) {
            log("No requests selected.");
            return;
        }

        try {
            requestService.acceptRequest(selected);
            log("Accepted request from " + selected.getFrom().getUsername());
        } catch (Exception e) {
            log("Error: " + e.getMessage());
        }
    }

    @FXML
    public void onReject() {
        FriendRequest selected = requestsList.getSelectionModel().getSelectedItem();
        if (selected == null)
            return;

        try {
            requestService.rejectRequest(selected);
            log("Rejected request from " + selected.getFrom().getUsername());
        } catch (Exception e) {
            log("Error: " + e.getMessage());
        }
    }

    @FXML
    public void onStats() {
        log("--- Community Stats ---");
        try {
            log("Communities count: " + community.countCommunities());

            var soc = community.mostSociableCommunity();
            log("Most Sociable Diameter: " + soc.diameter());
            log("Number of Members: " + soc.members().size());
            log("Members: ");
            soc.members().forEach(u -> log(" - " + u.getUsername() + " (ID: " + u.getId() + ")"));
        } catch (Exception e) {
            log("Error calculating stats: " + e.getMessage());
        }
    }

    public void cleanup() {
        if (requestService != null)
            requestService.removeObserver(this);
    }
}

//    @FXML
//    public void onAddPerson() {
//        // Dialog form
//        Dialog<Person> dialog = new Dialog<>();
//        dialog.setTitle("New Person");
//        dialog.setHeaderText("Create a new Person");
//
//        // Buttons
//        ButtonType createBtn = new ButtonType("Create", ButtonBar.ButtonData.OK_DONE);
//        dialog.getDialogPane().getButtonTypes().addAll(createBtn, ButtonType.CANCEL);
//
//        // Layout
//        GridPane grid = new GridPane();
//        grid.setHgap(10);
//        grid.setVgap(10);
//        grid.setPadding(new Insets(20, 150, 10, 10));
//
//        TextField username = new TextField();
//        TextField email = new TextField();
//        TextField password = new PasswordField();
//        TextField name = new TextField();
//        TextField firstName = new TextField();
//        DatePicker birthDate = new DatePicker(LocalDate.now().minusYears(18));
//        TextField job = new TextField();
//
//        grid.addRow(0, new Label("Username:"), username);
//        grid.addRow(1, new Label("Email:"), email);
//        grid.addRow(2, new Label("Password:"), password);
//        grid.addRow(3, new Label("Last name:"), name);
//        grid.addRow(4, new Label("First nanme:"), firstName);
//        grid.addRow(5, new Label("Job:"), job);
//        grid.addRow(6, new Label("Birth date:"), birthDate);
//
//        dialog.getDialogPane().setContent(grid);
//
//        dialog.setResultConverter(dialogButton -> {
//            if (dialogButton == createBtn)
//                try {
//                    return users.createPerson(username.getText(), email.getText(), password.getText(),
//                            name.getText(), firstName.getText(), birthDate.getValue(), job.getText());
//                } catch (Exception e) {
//                    log("Error: " + e.getMessage());
//                }
//            return null;
//        });
//
//        dialog.showAndWait().ifPresent(p -> log("SUCCESS: Created Person ID " + p.getId()));
//    }
//
//    @FXML
//    public void onAddDuck() {
//        Dialog<Duck> dialog = new Dialog<>();
//        dialog.setTitle("New Duck");
//        dialog.setHeaderText("Create a new Duck");
//
//        ButtonType createBtn = new ButtonType("Create", ButtonBar.ButtonData.OK_DONE);
//        dialog.getDialogPane().getButtonTypes().addAll(createBtn, ButtonType.CANCEL);
//
//        GridPane grid = new GridPane();
//        grid.setHgap(10);
//        grid.setVgap(10);
//        grid.setPadding(new Insets(20, 150, 10, 10));
//
//        TextField username = new TextField();
//        TextField email = new TextField();
//        PasswordField password = new PasswordField();
//        ComboBox<String> type = new ComboBox<>(FXCollections.observableArrayList("SWIMMING", "FLYING", "HYBRID"));
//        type.getSelectionModel().selectFirst();
//        TextField speed = new TextField();
//        TextField resistance = new TextField();
//
//        grid.addRow(0, new Label("Username:"), username);
//        grid.addRow(1, new Label("Email:"), email);
//        grid.addRow(2, new Label("Password:"), password);
//        grid.addRow(3, new Label("Speed:"), speed);
//        grid.addRow(4, new Label("Resistance:"), resistance);
//        grid.addRow(5, new Label("Type"), type);
//
//        dialog.getDialogPane().setContent(grid);
//
//        dialog.setResultConverter(dialogButton -> {
//            if (dialogButton == createBtn)
//                try {
//                    String u = username.getText();
//                    String e = email.getText();
//                    String p = password.getText();
//                    double s = Double.parseDouble(speed.getText());
//                    double r = Double.parseDouble(resistance.getText());
//                    String t = type.getValue();
//
//                    if (t.equals("SWIMMING"))
//                        return users.createSwimmingDuck(u, e, p, s, r);
//                    if (t.equals("FLYING"))
//                        return users.createFlyingDuck(u, e, p, s, r);
//                    return users.createHybridDuck(u, e, p, s, r);
//                } catch (Exception e) {
//                    log("Error: " + e.getMessage());
//                }
//            return null;
//        });
//

//        dialog.showAndWait().ifPresent(d -> log("SUCCESS: Created Duck ID " + d.getId()));

//    }
//    @FXML
//    public void onAddFriend() {
//        String id1 = ask("Friendship", "ID of first user: ");
//        if (id1 == null)
//            return;
//
//        String id2 = ask("Friendship", "ID of second user:");
//        if (id2 == null)
//            return;
//
//        try {
//            friends.addFriendship(Long.parseLong(id1), Long.parseLong(id2));
//            log("SUCCESS: Friendship added.");
//        } catch (Exception e) {
//            log("ERROR: " + e.getMessage());
//        }
//    }
//
//    @FXML
//    public void onRemoveFriend() {
//        String id1 = ask("Unfriend", "ID of first user: ");
//        if (id1 == null)
//            return;
//
//        String id2 = ask("Unfriend", "ID of second user:");
//        if (id2 == null)
//            return;
//
//        try {
//            long firstId = Long.parseLong(id1);
//            long secondId = Long.parseLong(id2);
//            friends.removeFriendship(firstId, secondId);
//            log("SUCCESS: Friendship removed.");
//        } catch (Exception e) {
//            log("ERROR: " + e.getMessage());

//        }
//    }

//    private String ask(String title, String content) {
//        TextInputDialog dialog = new TextInputDialog();
//
//        dialog.setTitle(title);
//        dialog.setHeaderText(null);
//        dialog.setContentText(content);
//
//        Optional<String> result = dialog.showAndWait();
//        return result.orElse(null);
//    }
//
//    @FXML
//    public void onDeleteUser() {
//
//        TextInputDialog dialog = new TextInputDialog();
//        dialog.setTitle("Delete User");
//        dialog.setContentText("User ID:");
//        dialog.showAndWait().ifPresent(idStr -> {
//            try {
//                users.deleteUser(Long.parseLong(idStr));
//                friends.syncWithUsers();
//                log("SUCCESS: User " + idStr + " deleted.");
//            } catch (Exception e) {
//                log("ERROR: " + e.getMessage());
//            }
//        });
//    }

