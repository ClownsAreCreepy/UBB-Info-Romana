package scs.ui;

import javafx.application.Platform;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import scs.domain.Transaction;
import scs.domain.User;
import scs.service.MarketService;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observer;

import java.time.format.DateTimeFormatter;
import java.util.Comparator;
import java.util.List;

public class AdminController implements Observer<EntityChangeEvent<Object>> {
    @FXML
    private TableView<Transaction> transTable;

    @FXML
    private TableColumn<Transaction, String> colTime;
    @FXML
    private TableColumn<Transaction, String> colTrader;
    @FXML
    private TableColumn<Transaction, String> colType;
    @FXML
    private TableColumn<Transaction, String> colCoin;
    @FXML
    private TableColumn<Transaction, String> colPrice;


    private MarketService service;
    private ObservableList<Transaction> model = FXCollections.observableArrayList();
    private final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm:ss");

    public void setService(MarketService service) {
        this.service = service;
        this.service.addObserver(this);

        colTime.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getTimestamp().format(formatter)));

        colTrader.setCellValueFactory(cell -> {
            Long userId = cell.getValue().getUserid();

            String name = service.getAllUsers().stream()
                    .filter(u -> u.getId().equals(userId))
                    .map(User::getName)
                    .findFirst().orElse("Unknown");

            return new SimpleStringProperty(name);
        });

        colType.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getType()));
        colCoin.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getCoinsymbol()));
        colPrice.setCellValueFactory(cell -> new SimpleStringProperty(String.format("%.2f", cell.getValue().getPrice())));

        transTable.setItems(model);

        refreshData();
    }

    private void refreshData() {
        List<Transaction> all = service.getAllTransactions();

        all.sort(Comparator.comparing(Transaction::getTimestamp).reversed());
        model.setAll(all);
    }


    @Override
    public void update(EntityChangeEvent<Object> event) {
        Platform.runLater(this::refreshData);
    }
}
