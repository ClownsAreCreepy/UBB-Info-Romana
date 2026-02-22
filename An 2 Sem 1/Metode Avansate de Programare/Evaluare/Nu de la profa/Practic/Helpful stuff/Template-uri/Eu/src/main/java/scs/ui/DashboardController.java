package scs.ui;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observer;
import scs.domain.Entity; // CHANGE TO YOUR DOMAIN
import scs.service.GenericService;

public class DashboardController implements Observer<EntityChangeEvent<Entity>> {
    @FXML private TableView<Entity> table;
    @FXML private TableColumn<Entity, Long> colId;
    // @FXML private TableColumn<Entity, String> colName; // Add columns here
    @FXML private Label infoLabel;

    private GenericService<Entity> service;
    private ObservableList<Entity> model = FXCollections.observableArrayList();

    public void setService(GenericService<Entity> service) {
        this.service = service;
        this.service.addObserver(this);

        // Setup Table
        colId.setCellValueFactory(new PropertyValueFactory<>("id"));
        // colName.setCellValueFactory(new PropertyValueFactory<>("name"));

        table.setItems(model);

        // Load Data
        model.setAll(service.getAll());
    }

    @Override
    public void update(EntityChangeEvent<Entity> event) {
        Platform.runLater(() -> {
            Entity data = event.data();
            switch (event.type()) {
                case ADD -> model.add(data);
                case DELETE -> model.removeIf(x -> x.getId().equals(data.getId()));
                case UPDATE -> {
                    for(int i=0; i<model.size(); i++)
                        if(model.get(i).getId().equals(data.getId())) {
                            model.set(i, data);
                            break;
                        }
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