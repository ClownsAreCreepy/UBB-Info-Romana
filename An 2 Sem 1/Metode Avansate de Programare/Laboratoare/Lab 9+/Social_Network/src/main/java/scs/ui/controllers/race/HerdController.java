package scs.ui.controllers.race;

import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.scene.control.*;
import scs.domain.group.Herd;
import scs.domain.group.Performance;
import scs.domain.user.Duck;
import scs.domain.user.User;
import scs.service.HerdService;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observer;

import javafx.fxml.FXML;
import javafx.scene.layout.VBox;
import javafx.collections.FXCollections;
import javafx.concurrent.Task;

public class HerdController implements Observer<EntityChangeEvent<Herd<Duck>>> {
    @FXML
    private ListView<Herd<Duck>> herdList;
    @FXML
    private TextField newHerdName;
    @FXML
    private VBox detailsBox;
    @FXML
    private Label lblHerdName;
    @FXML
    private Label lblStats;
    @FXML
    private ListView<Duck> memberList;
    @FXML
    private Button actionBtn;

    private final ObservableList<Herd<Duck>> herdsModel = FXCollections.observableArrayList();
    private final ObservableList<Duck> membersModel = FXCollections.observableArrayList();

    private HerdService herdService;
    private User currentUser;
    private boolean isDuck;

    private Herd<Duck> currentDisplayedHerd;

    public void setService(HerdService hs, User user) {
        this.herdService = hs;
        this.currentUser = user;
        this.isDuck = (user instanceof Duck);

        this.herdService.addObserver(this);

        initUI();
        herdsModel.setAll(herdService.getAll());
        // System.out.println("HerdController init: User=" + user.getUsername() + ", isDuck=" + isDuck);
    }

    private void initUI() {
        herdList.setItems(herdsModel);
        memberList.setItems(membersModel);

        herdList.getSelectionModel().selectedItemProperty().addListener((obs, oldVal, newVal) -> {

            if (newVal != null)
                fetchAndShowDetails(newVal);
            else {
                detailsBox.setVisible(false);
                currentDisplayedHerd = null;
            }
        });
    }

    @Override
    public void update(EntityChangeEvent<Herd<Duck>> event) {
        Platform.runLater(() -> {
            Herd<Duck> data = event.data();

            boolean wasSelected = isCurrentSelection(data.getId());

            switch (event.type()) {
                case ADD:
                    herdsModel.add(data);
                    break;

                case DELETE:
                    herdsModel.removeIf(h -> h.getId().equals(data.getId()));

                    if (isCurrentSelection(data.getId())) {
                        detailsBox.setVisible(false);
                        currentDisplayedHerd = null;
                        herdList.getSelectionModel().clearSelection();
                    }
                    break;

                case UPDATE:
                    int idx = findIndexById(data.getId());
                    if (idx != -1) {
                        herdsModel.set(idx, data);

                        if (wasSelected) {
                            herdList.getSelectionModel().select(idx);
                            updateDetailsUi(data);
                        }
                    }
                    break;
            }
        });
    }

    private int findIndexById(Long id) {
        for (int i = 0; i < herdList.getItems().size(); ++i)
            if (herdList.getItems().get(i).getId().equals(id))
                return i;
        return -1;
    }

    private boolean isCurrentSelection(Long herdId) {
        Herd<Duck> selected = herdList.getSelectionModel().getSelectedItem();
        return selected != null && selected.getId().equals(herdId);
    }

    private void fetchAndShowDetails(Herd<Duck> herd) {
        detailsBox.setVisible(true);
        lblHerdName.setText(herd.getName());
        lblStats.setText("Loading stats...");

        // Clear list immediately to show we are working
        memberList.getItems().clear();

        // Create a background task
        Task<Void> task = new Task<>() {
            @Override
            protected Void call() {
                // This runs background thread
                // 1. Force a fresh fetch from DB
                Herd<Duck> freshHerd = herdService.findById(herd.getId());

                // 3. Update UI on the JavaFx Application Thread
                Platform.runLater(() -> updateDetailsUi(freshHerd));

                return null;
            }
        };

        // Handle errors
        task.setOnFailed(e -> {
            lblStats.setText("Error loading data");
            showAlert("Failed to load herd details: " + task.getException().getMessage());
        });

        new Thread(task).start();
    }

    private void updateDetailsUi(Herd<Duck> herd) {
        currentDisplayedHerd = herd;

        lblHerdName.setText(herd.getName());

        Performance stats = herd.getAvgPerformance();
        lblStats.setText(String.format("Avg Speed: %.2f | Avg Res: %.2f",
                stats.avgSpeed(), stats.avgResistance()));

        membersModel.setAll(herd.getMembers());
        updateActionButtonState(herd);
    }

    private boolean isMemberOf(Herd<Duck> herd) {
        if (herd == null || herd.getMembers() == null)
            return false;
        return herd.getMembers().stream().anyMatch(d -> d.getId().equals(currentUser.getId()));
    }

    private void updateActionButtonState(Herd<Duck> herd) {
        if (!isDuck) {
            actionBtn.setText("Spectator Only");
            actionBtn.setDisable(true);
            actionBtn.setStyle("-fx-background-color: #bdc3c7; -fx-text-fill: #7f8c8d;");
            return;
        }

        boolean isMember = isMemberOf(herd);
        actionBtn.setDisable(false);

        if (isMember) {
            actionBtn.setText("Leave Herd");
            actionBtn.setStyle("-fx-background-color: #e74c3c; -fx-text-fill: white; -fx-font-weight: bold;");
        } else {
            actionBtn.setText("Join Herd");
            actionBtn.setStyle("-fx-background-color: #27ae60; -fx-text-fill: white; -fx-font-weight: bold;");
        }
    }

    @FXML
    public void onActionBtnClicked() {
        Herd<Duck> selectedHerd = this.currentDisplayedHerd;

        if (selectedHerd == null || !isDuck) return;

        try {
            boolean isMember = isMemberOf(selectedHerd);

            if (isMember)
                herdService.deleteDuck(selectedHerd.getId(), currentUser.getId());
            else {
                herdService.addDuck(selectedHerd.getId(), (Duck) currentUser);
                // System.out.println(currentUser.getUsername() + " joined herd " + selectedHerd.getName());
            }
        } catch (Exception e) {
            new Alert(Alert.AlertType.ERROR, "Action failed: " + e.getMessage()).show();
        }
    }

    private void showAlert(String msg) {
        new Alert(Alert.AlertType.ERROR, msg).show();
    }

    @FXML
    public void onCreateHerd() {
        if (!isDuck) {
            showAlert("Only ducks can create herds!");
            newHerdName.clear();
            return;
        }

        String name = newHerdName.getText();
        if (name.isBlank())
            return;

        try {
            Herd<Duck> newHerd = herdService.createHerd(name);

            herdService.addDuck(newHerd.getId(), (Duck) currentUser);

            newHerdName.clear();

            // herdList.getSelectionModel().select(newHerd); -> it's kinda async
        } catch (Exception e) {
            showAlert("Creation Failed: " + e.getMessage());
        }
    }

    public void cleanup() {
        if (herdService != null)
            herdService.removeObserver(this);
    }
}

//    @FXML
//    public void onAddDuck() {
//        Herd<Duck> selected = herdList.getSelectionModel().getSelectedItem();
//        if (selected == null)
//            return;
//
//        try {
//            long duckId = Long.parseLong(duckIdInput.getText());
//
//            User u = userService.findById(duckId);
//            if (u instanceof Duck d) {
//                herdService.addDuck(selected.getId(), d);
//                showDetails(selected);  // refresh
//                refreshMasterList();
//                duckIdInput.clear();
//            } else
//                showAlert("Error: Not a Duck!");
//        } catch (Exception e) {
//            showAlert("Error: " + e.getMessage());
//        }
//    }
//
//    @FXML
//    public void onRemoveDuck() {
//        Herd<Duck> selectedHerd = herdList.getSelectionModel().getSelectedItem();
//        Duck selectedDuck = memberList.getSelectionModel().getSelectedItem();
//
//        if (selectedHerd != null && selectedDuck != null) {
//            herdService.deleteDuck(selectedHerd.getId(), selectedDuck.getId());
//            showDetails(selectedHerd);  // refresh
//            refreshMasterList();
//        }
//    }
//    @FXML
//    public void onDeleteHerd() {
//        Herd<Duck> selected = herdList.getSelectionModel().getSelectedItem();
//        if (selected == null)
//            return;
//
//        herdService.deleteHerd(selected.getId());
//        refreshMasterList();
//        detailsBox.setVisible(false);
//    }
