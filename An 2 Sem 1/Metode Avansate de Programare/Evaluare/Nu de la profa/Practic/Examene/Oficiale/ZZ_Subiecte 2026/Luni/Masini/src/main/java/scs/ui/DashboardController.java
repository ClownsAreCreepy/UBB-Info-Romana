package scs.ui;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import scs.domain.Car;
import scs.domain.User;
import scs.service.CarService;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observer;
import scs.service.GenericService;

import java.util.Optional;

public class DashboardController implements Observer<EntityChangeEvent<Car>> {
    @FXML private TableView<Car> table;
    @FXML private TableColumn<Car, Long> colId;
    @FXML private TableColumn<Car, String> colDenumire;
    @FXML private TableColumn<Car, String> colDescriere;
    @FXML private TableColumn<Car, Integer> colPret;
    @FXML private TableColumn<Car, String> colStatus;

    @FXML private Label userLabel;
    @FXML private Label notificationLabel;

    private CarService service;
    private User currentUser;
    private ObservableList<Car> model = FXCollections.observableArrayList();

    public void setService(CarService service, User user) {
        this.service = service;
        this.currentUser = user;
        this.service.addObserver(this);

        userLabel.setText("Logged in as: " + user.getUsername() + " [" + user.getRole() + "]");

        initTable();
        loadData();

        // Setup Double Click Action
        table.setRowFactory(tv -> {
            TableRow<Car> row = new TableRow<>();
            row.setOnMouseClicked(event -> {
                if (event.getClickCount() == 2 && (!row.isEmpty()))
                    handleRowAction(row.getItem());
            });
            return row;
        });
    }

    private void initTable() {
        colId.setCellValueFactory(new PropertyValueFactory<>("id"));
        colDenumire.setCellValueFactory(new PropertyValueFactory<>("denumire"));
        colDescriere.setCellValueFactory(new PropertyValueFactory<>("descriere"));
        colPret.setCellValueFactory(new PropertyValueFactory<>("pret"));
        colStatus.setCellValueFactory(new PropertyValueFactory<>("status"));
        table.setItems(model);
    }

    private void loadData() {
        model.clear();
        if ("ADMIN".equals(currentUser.getRole())) {
            model.setAll(service.getPendingCars());
        } else {
            model.setAll(service.getAll());
        }
    }

    // logic for actions
    private void handleRowAction(Car car) {
        if (currentUser.getRole().equals("DEALER"))
            if (car.getStatus().equals("NEW"))
                showDealerDialog(car, "Send for approval?");
            else if (car.getStatus().equals("REJECTED"))
                showDealerDialog(car, "Fixing Rejection (Reason: " + car.getComment() + ")");
            else
                showAlert("Action not allowed", "You can only request approval for NEW or REJECTED cars.");
        else
            showAdminDialog(car);
    }

    // dialogs
    private void showDealerDialog(Car car, String header) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Request Approval");
        dialog.setHeaderText(header);
        dialog.setContentText("Add Comment:");

        Optional<String> result = dialog.showAndWait();
        result.ifPresent(comment -> {
            service.requestApproval(car, comment);
            showAlert("Success", "Request sent!");
        });
    }

    private void showAdminDialog(Car car) {
        Alert alert = new Alert (Alert.AlertType.CONFIRMATION);
        alert.setTitle("Review Request");
        alert.setHeaderText("Dealer comment: " + car.getComment());
        alert.setContentText("Approve or Reject?");

        ButtonType btnApprove = new ButtonType("Approve");
        ButtonType btnReject = new ButtonType("Reject");
        ButtonType btnCancel = new ButtonType("Cancel", ButtonBar.ButtonData.CANCEL_CLOSE);

        alert.getButtonTypes().setAll(btnApprove, btnReject, btnCancel);

        Optional<ButtonType> result = alert.showAndWait();
        if (result.isPresent()) {
            if (result.get() == btnApprove) {
                service.approveCar(car);
            } else if (result.get() == btnReject) {
                TextInputDialog rejectDialog = new TextInputDialog();
                rejectDialog.setTitle("Reject Reason");
                rejectDialog.setHeaderText("Why are you rejecting?");
                rejectDialog.showAndWait().ifPresent(reason -> {
                    service.rejectCar(car, reason);
                });
            }
        }
    }

    // observer
    @Override
    public void update(EntityChangeEvent<Car> event) {
        Platform.runLater(() -> {
            loadData();

            if (currentUser.getRole().equals("ADMIN")) {
                boolean hasPending = service.getAll().stream()
                        .anyMatch(c -> c.getStatus().equals("NEEDS_APPROVAL"));
                notificationLabel.setText("New request pending!");
                notificationLabel.setStyle("-fx-text-fill: red; -fx-font-weight: bold;");
                notificationLabel.setVisible(hasPending);
            } else {
                Car changedCar = event.data();
                if (changedCar.getStatus().equals("APPROVED") ||  changedCar.getStatus().equals("REJECTED")) {
                    notificationLabel.setText("Update: Car " + changedCar.getDenumire() + " is " + changedCar.getStatus());
                    notificationLabel.setStyle("-fx-text-fill: green; -fx-font-weight: bold;");
                    notificationLabel.setVisible(true);
                }
            }
        });
    }

    private void showAlert(String title, String message) {
        Alert a = new Alert(Alert.AlertType.INFORMATION);
        a.setTitle(title);
        a.setContentText(message);
        a.show();
    }

    public void close() { service.removeObserver(this); }
}

/*
    private void initTable() {
        colId.setCellValueFactory(new PropertyValueFactory<>("id"));
        colName.setCellValueFactory(new PropertyValueFactory<>("name")); // Ensure getName() exists
        mainTable.setItems(model);
    }

    private void loadData() {
        model.setAll(service.getAll());
    }

    @FXML
    public void onAsyncAction() {
        Entity selected = table.getSelectionModel().getSelectedItem();
        if (selected == null) return;

        infoLabel.setText("Processing... (5s)");

        service.processAsync(selected, () -> {
            // LOGIC GOES HERE (Background Thread)
            // e.g. selected.setStatus("ACCEPTED");
            // service.update(selected);
            System.out.println("Async task finished for " + selected.getId());
        });
    }
 */