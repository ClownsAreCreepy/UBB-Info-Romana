package scs.ui;

import javafx.application.Platform;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import scs.domain.Coin;
import scs.domain.User;
import scs.service.MarketService;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observer;

public class TraderController implements Observer<EntityChangeEvent<Object>> {
    @FXML
    private Label nameLabel;

    @FXML private Label budgetLabel;

    @FXML private Label statusLabel;

    @FXML private TableView<Coin> coinsTable;
    @FXML private TableColumn<Coin, String> colSymbol;
    @FXML private TableColumn<Coin, String> colName;
    @FXML private TableColumn<Coin, Double> colPrice;

    @FXML private Button btnBuy;
    @FXML private Button btnSell;

    private MarketService service;
    private User currentUser;
    private ObservableList<Coin> model = FXCollections.observableArrayList();

    public void setService(MarketService service, User user) {
        this.service = service;
        this.currentUser = user;
        this.service.addObserver(this);

        nameLabel.setText("Trader: " + currentUser.getName());
        updateBudgetLabel();

        colSymbol.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getSymbol()));
        colName.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getName()));
        colPrice.setCellValueFactory(cell -> new SimpleObjectProperty<>(cell.getValue().getPrice()));

        coinsTable.setItems(model);

        refreshData();
    }

    private void updateBudgetLabel() {
        // re-fetch to make sure we have the latest budget
        User freshUser = service.getAllUsers().stream()
                .filter(u -> u.getId().equals(currentUser.getId())).findFirst().orElse(currentUser);

        this.currentUser = freshUser;
        budgetLabel.setText(String.format("Budget: %.2f", currentUser.getBudget()));
    }

    private void refreshData() {
        model.setAll(service.getAllCoins());
        updateBudgetLabel();
    }

    @Override
    public void update(EntityChangeEvent<Object> event) {
        Platform.runLater(this::refreshData);
    }

    private void handleTransaction(String type) {
        Coin selected = coinsTable.getSelectionModel().getSelectedItem();
        if (selected == null) {
            showAlert("Error", "No coin selected!");
            return;
        }

        statusLabel.setText("Processing " + type + "...");

        service.processTransactionAsync(currentUser.getId(), selected.getSymbol(), type);
    }

    @FXML
    public void onBuy() {
        handleTransaction("BUY");
    }

    @FXML
    public void onSell() {
        handleTransaction("SELL");
    }

    private void showAlert(String title, String content) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setContentText(content);
        alert.show();
    }

    // Cleanup to prevent memory leaks
    public void close() {
        service.removeObserver(this);
    }
}
