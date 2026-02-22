package scs.ui.controllers.social;

import javafx.application.Platform;
import javafx.beans.binding.Bindings;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.ObservableList;
import javafx.concurrent.Task;
import javafx.scene.Scene;
import javafx.stage.Stage;
import scs.domain.user.*;
import scs.service.social.UserService;
import scs.service.friend.FriendshipService;
import scs.service.friend.RequestService;
import scs.ui.pages.ProfilePage;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observer;
import scs.utilities.paging.*;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.util.Set;

public class UserController implements Observer<EntityChangeEvent<User>> {

    @FXML
    private TableView<User> usersTable;

    // Columns
    @FXML
    private TableColumn<User, Long> colId;
    @FXML
    private TableColumn<User, String> colUser;
    @FXML
    private TableColumn<User, String> colEmail;

    @FXML
    private TableColumn<User, String> colName;
    @FXML
    private TableColumn<User, String> colJob;

    @FXML
    private TableColumn<User, Double> colSpeed;
    @FXML
    private TableColumn<User, Double> colRes;

    // Filters
    @FXML
    private ComboBox<String> duckTypeCombo;
    @FXML
    private ComboBox<String> userTypeCombo;
    @FXML
    private ComboBox<String> relationCombo;

    // Pagination
    @FXML
    private TextField pageSizeInput;
    @FXML
    private Label pageLabel;

    private int currentPage = 0;
    private int pageSize = 5;
    private int totalRecords = 0;

    private ContextMenu activeMenu = null;

    // Services
    private UserService userService;
    private RequestService requestService;
    private FriendshipService friendshipService;
    private User currentUser;

    private final ObservableList<User> tableModel = FXCollections.observableArrayList();

    public void setContext(UserService service, RequestService reqService,
                           FriendshipService friendService, User loggedIn) {
        this.userService = service;
        this.requestService = reqService;
        this.friendshipService = friendService;
        this.currentUser = loggedIn;

        this.userService.addObserver(this);

        initColumns();
        initFilters();
        initContextMenu();

        usersTable.setItems(tableModel);
        loadUsersBackground();
    }

    @Override
    public void update(EntityChangeEvent<User> event) {
        Platform.runLater(() -> {
            User data = event.data();
            switch (event.type()) {
                case ADD:
                    totalRecords++;
                    updatePageLabel();

                    if (!passesFilters(data))
                        return;

                    int targetPage = (totalRecords - 1) / pageSize;

                    if (currentPage == targetPage)
                        tableModel.add(data);
                    break;

                case DELETE:
                    loadUsersBackground();
                    break;

                case UPDATE:
                    int idx = findIndexById(data.getId());
                    if (idx != -1) {
                        tableModel.set(idx, data);
                        usersTable.refresh();
                    }
                    break;
            }
        });
    }

    private boolean passesFilters(User u) {
        String uType = userTypeCombo.getValue();
        if (uType.equals("PERSON") && !(u instanceof Person)) return false;
        if (uType.equals("DUCK") && !(u instanceof Duck)) return false;

        if (u instanceof Duck) {
            String dType = duckTypeCombo.getValue();
            if (dType.equals("SWIMMING") && !(u instanceof SwimmingDuck)) return false;
            if (dType.equals("FLYING") && !(u instanceof FlyingDuck)) return false;
            if (dType.equals("HYBRID") && !(u instanceof HybridDuck)) return false;
        }

        String rel = relationCombo.getValue();
        if (!"ALL".equals(rel)) {
            boolean areFriends = friendshipService.areFriends(currentUser.getId(), u.getId());

            if (rel.equals("FRIENDS") && !areFriends) return false;
            if (rel.equals("NOT FRIENDS") && areFriends) return false;
        }

        return true;
    }

    private int findIndexById(Long id) {
        for (int i = 0; i < tableModel.size(); ++i)
            if (tableModel.get(i).getId().equals(id))
                return i;

        return -1;
    }

    private void initColumns() {
        colId.setCellValueFactory(new PropertyValueFactory<>("id"));
        colUser.setCellValueFactory(new PropertyValueFactory<>("username"));
        colEmail.setCellValueFactory(new PropertyValueFactory<>("email"));

        colName.setCellValueFactory(cellData -> {
            if (cellData.getValue() instanceof Person p)
                return new SimpleStringProperty(p.getFullName());
            return new SimpleStringProperty("-");
        });
        colJob.setCellValueFactory(cellData -> {
            if (cellData.getValue() instanceof Person p)
                return new SimpleStringProperty(p.getOccupation());
            return new SimpleStringProperty("-");
        });

        colSpeed.setCellValueFactory(cellData -> {
            if (cellData.getValue() instanceof Duck d)
                return new SimpleObjectProperty<>(d.getSpeed());
            return null;
        });

        colRes.setCellValueFactory(cellData -> {
            if (cellData.getValue() instanceof Duck d)
                return new SimpleObjectProperty<>(d.getResistance());
            return null;
        });
    }

    private void initFilters() {
        userTypeCombo.setItems(FXCollections.observableArrayList("ALL", "PERSON", "DUCK"));
        userTypeCombo.getSelectionModel().select("ALL");

        duckTypeCombo.setItems(FXCollections.observableArrayList("ALL", "SWIMMING", "FLYING", "HYBRID"));
        duckTypeCombo.getSelectionModel().select("ALL");
        duckTypeCombo.setVisible(false);
        duckTypeCombo.setManaged(false);

        relationCombo.setItems(FXCollections.observableArrayList("ALL", "FRIENDS", "NOT FRIENDS"));
        relationCombo.getSelectionModel().select("ALL");

        userTypeCombo.setOnAction(e -> {
            String selected = userTypeCombo.getValue();
            boolean isDuckMode = "DUCK".equals(selected);

            duckTypeCombo.setVisible(isDuckMode);
            duckTypeCombo.setManaged(isDuckMode);

            if (!isDuckMode)
                duckTypeCombo.getSelectionModel().select("ALL");

            this.currentPage = 0;
            loadUsersBackground();
        });

        duckTypeCombo.setOnAction(e -> {
            currentPage = 0;
            loadUsersBackground();
        });

        relationCombo.setOnAction(e -> {
            currentPage = 0;
            loadUsersBackground();
        });
    }

    private void initContextMenu() {
        usersTable.setRowFactory(tv -> {
            TableRow<User> row = new TableRow<>();

            row.setOnContextMenuRequested(e -> {
                User target = row.getItem();

                if (target == null) {
                    return;
                }

                if (activeMenu != null) {
                    activeMenu.hide();
                }

                ContextMenu menu = new ContextMenu();
                activeMenu = menu;

                menu.getItems().clear();

                MenuItem viewProfile = new MenuItem("View Profile");
                viewProfile.setOnAction(event -> openProfileWindow(target));
                menu.getItems().add(viewProfile);

                if (!target.getId().equals(currentUser.getId())) {
                    boolean isFriend = friendshipService.areFriends(currentUser.getId(), target.getId());

                    if (isFriend) {
                        MenuItem removeFriend = new MenuItem("Remove Friend");
                        removeFriend.setStyle("-fx-text-fill: #e74c3c;");
                        removeFriend.setOnAction(event -> removeFriendship(target));
                        menu.getItems().add(removeFriend);
                    } else {
                        MenuItem sendReq = new MenuItem("Send Friend Request");
                        sendReq.setOnAction(event -> sendFriendRequest(target));
                        menu.getItems().add(sendReq);
                    }
                }

                menu.show(row, e.getScreenX(), e.getScreenY());
            });

            return row;
        });
    }

    private void removeFriendship(User target) {
        Alert confirm = new Alert(Alert.AlertType.CONFIRMATION,
                "Are you sure you want to remove " + target.getUsername() + " from you friends?");

        confirm.showAndWait().ifPresent(response -> {
            if (response == ButtonType.OK) {
                try {
                    friendshipService.removeFriendship(currentUser.getId(), target.getId());
                    if (!relationCombo.getValue().equals("ALL"))
                        loadUsersBackground();
                } catch (Exception e) {
                    new Alert(Alert.AlertType.ERROR, "Could not remove friendship: " +e.getMessage()).show();
                }
            }
        });
    }

    private void sendFriendRequest(User target) {
        try {
            requestService.sendRequest(currentUser.getId(), target.getId());
            new Alert(Alert.AlertType.INFORMATION, "Friend request sent to " + target.getUsername()).show();
        } catch (Exception e) {
            new Alert(Alert.AlertType.ERROR, e.getMessage()).show();
        }
    }

    private void openProfileWindow(User target) {
        try {
            boolean isFriend = friendshipService.areFriends(currentUser.getId(), target.getId());

            ProfilePage page = new ProfilePage(target, false, isFriend, userService, null);

            Stage stage = new Stage();
            stage.setTitle("Profile: " + target.getUsername());
            stage.setScene(new Scene(page.getView()));

            stage.setResizable(false);

            stage.show();
        } catch (Exception e) {
            new Alert(Alert.AlertType.ERROR, "Could not open profile: " + e.getMessage()).show();
            e.printStackTrace();
        }
    }

    private void loadUsersBackground() {
        if (currentUser == null)
            return;

        pageLabel.setText("Loading...");

        String uType = userTypeCombo.getValue();
        String dType = duckTypeCombo.getValue();
        String relType = relationCombo.getValue();
        Pageable p = new Pageable(currentPage, pageSize);

        Task<Page<User>> task = new Task<>() {
            @Override
            protected Page<User> call() {
                Set<Long> friendIds = friendshipService.getFriendsOf(currentUser.getId());
                return userService.searchUsers(p, uType, dType, relType, currentUser.getId(), friendIds);
            }
        };

        task.setOnSucceeded(e -> {
            Page<User> res = task.getValue();
            tableModel.setAll(res.getElementsOnPage());
            totalRecords = res.getTotalElementCount();
            updatePageLabel();
        });

        task.setOnFailed(e -> {
            pageLabel.setText("Error loading data.");
            new Alert(Alert.AlertType.ERROR, "Failed to load users: " + task.getException().getMessage()).show();
        });

        new Thread(task).start();
    }

    private void updatePageLabel() {
        int totalPages = (int) Math.ceil((double) totalRecords / pageSize);
        if (totalPages == 0)
            totalPages = 1;

        pageLabel.setText("Page " + (currentPage + 1) + " of " + totalPages);
    }

    @FXML
    public void onSetPageSize() {
        try {
            int newSize = Integer.parseInt(pageSizeInput.getText());
            if (newSize > 0) {
                this.pageSize = newSize;
                this.currentPage = 0;
                loadUsersBackground();
            } else {
                pageSizeInput.setText(String.valueOf(pageSize));
            }
        } catch (NumberFormatException e) {
            pageSizeInput.clear();
        }
    }

    @FXML
    public void onNextPage() {
        int totalPages = (int) Math.ceil((double) totalRecords / pageSize);
        if (currentPage < totalPages - 1) {
            currentPage++;
            loadUsersBackground();
        }
    }

    @FXML
    public void onPrevPage() {
        if (currentPage > 0) {
            currentPage--;
            loadUsersBackground();
        }
    }

    public void cleanup() {
        if (userService != null)
            userService.removeObserver(this);
    }
}
