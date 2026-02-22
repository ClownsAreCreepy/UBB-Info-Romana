package com.example.template.controller;

import com.example.template.domeniu.*;
import com.example.template.events.UtilizatorEntityChangeEvent;
import com.example.template.observer.Observer;
import com.example.template.service.Service;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientController implements Observer<UtilizatorEntityChangeEvent> {

    @FXML
    private TextField adresa_field;

    @FXML
    private TableView<Oferta> tabel;

    @FXML
    private TableColumn<Oferta, String> sofer;

    @FXML
    private TableColumn<Oferta, Integer> minute;

    @FXML
    private TableColumn<Oferta, Void> actiuni;

    private ObservableList<Oferta> model = FXCollections.observableArrayList();
    private Service service;
    private Stage dialogStage;
    private Persoana persoana;

    // Setează serviciul și inițializează tabelul
    public void setService(Service service, Stage dialogStage, Persoana client) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.persoana = client;
        initModel();
        this.service.addObserver(this);
        this.dialogStage.setOnCloseRequest(event -> {
            this.service.removeObserver(this);
            this.service.removeActiveClient(client.getClientId());
            System.out.println("Observer removed.");
        });
    }
    @Override
    public void update(UtilizatorEntityChangeEvent event) {
        int active_users = service.getActiveUsers(client.getClientId());
        statuslabel.setText(active_users+" other users(s) are looking at the same location");
        //si model.setItems(service.getAll()) depinde de cerinta
    }
    @FXML
    public void initialize() {
        // Setează coloanele tabelului
        sofer.setCellValueFactory(cellData -> {
            Long idSofer = cellData.getValue().getId_sofer();
            Sofer sofer = service.getSofer(idSofer);
            return new SimpleStringProperty(sofer != null ? sofer.getNume() : "Necunoscut");
        });
        minute.setCellValueFactory(new PropertyValueFactory<>("minute"));

        // Configurează coloana de acțiuni cu butoanele "Acceptă" și "Refuză"
        actiuni.setCellFactory(param -> new TableCell<>() {
            private final Button btnAccepta = new Button("Acceptă");
            private final Button btnRefuza = new Button("Refuză");

            {
                btnAccepta.setOnAction(event -> {
                    Oferta oferta = getTableView().getItems().get(getIndex());
                    handleAcceptaOferta(oferta);
                });

                btnRefuza.setOnAction(event -> {
                    Oferta oferta = getTableView().getItems().get(getIndex());
                    handleRefuzaOferta(oferta);
                });
            }

            @Override
            protected void updateItem(Void item, boolean empty) {
                super.updateItem(item, empty);
                if (empty) {
                    setGraphic(null);
                } else {
                    HBox buttonsBox = new HBox(10, btnAccepta, btnRefuza);
                    setGraphic(buttonsBox);
                }
            }
        });

        tabel.setItems(model);
    }

    // Inițializează modelul tabelului
    private void initModel() {
        model.clear();
        List<Oferta> allOferte = StreamSupport.stream(service.getOferta().spliterator(), false)
                .filter(oferta -> oferta.getId_client().equals(persoana.getId()))
                .collect(Collectors.toList());
        allOferte.forEach(oferta -> System.out.println("Oferta ID: " + oferta.getId()));
        model.setAll(allOferte);
    }

    // Gestionează căutarea unei adrese
    public void handleCauta(ActionEvent actionEvent) {
        String adresa = adresa_field.getText();
        if (adresa.isEmpty()) {
            showErrorMessage("Adresa nu poate fi goală!");
            return;
        }
        service.save_cerere(new Cerere(persoana.getId(), adresa));
        showConfirmationMessage("Cerere trimisă!");
    }

    // Acceptă o ofertă
    private void handleAcceptaOferta(Oferta oferta) {
        System.out.println("Oferta acceptată: " + oferta);
        showConfirmationMessage("Ai acceptat oferta de la " + service.getSofer(oferta.getId_sofer()).getNume() + "!");
        service.delete_oferta(oferta.getId());
        service.saveComanda(new Comanda(service.getPersoana(persoana.getId()),service.getSofer(oferta.getId_sofer()), LocalDateTime.now()));
        service.delete_cerere_id(persoana.getId());
        initModel();
    }

    // Refuză o ofertă
    private void handleRefuzaOferta(Oferta oferta) {
        System.out.println("Oferta refuzata: " + oferta);
        showConfirmationMessage("Ai refuzat oferta de la " + service.getSofer(oferta.getId_sofer()).getNume() + "!");
        System.out.println(oferta.getId());
        service.delete_oferta(oferta.getId());
        initModel();
    }

    // Actualizează modelul când apar schimbări
    @Override
    public void update(UtilizatorEntityChangeEvent event) {
        initModel();
    }

    // Afișează un mesaj de eroare
    private void showErrorMessage(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Eroare");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    // Afișează un mesaj de confirmare
    private void showConfirmationMessage(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Confirmare");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }


    /*
    TABEL DINAMIC COMENZI RESTAUNRANTE
     public void initModel() {
        tableContainer.getChildren().clear();
        selectedItems.clear();
        Map<String, List<MenuItem>> menuByCategory = service.getMenuGroupedByCategory();
        for (Map.Entry<String, List<MenuItem>> entry : menuByCategory.entrySet()) {
            String category = entry.getKey();
            List<MenuItem> items = entry.getValue();

            Label categoryLabel = new Label(category);
            categoryLabel.setStyle("-fx-font-size: 16px; -fx-font-weight: bold; -fx-padding: 10 0 5 0;");

            TableView<MenuItem> tableView = new TableView<>();
            tableView.setPrefWidth(400);
            tableView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);

            TableColumn<MenuItem, String> itemColumn = new TableColumn<>("Item");
            itemColumn.setCellValueFactory(new PropertyValueFactory<>("item"));

            TableColumn<MenuItem, Float> priceColumn = new TableColumn<>("Price");
            priceColumn.setCellValueFactory(new PropertyValueFactory<>("pret"));

            TableColumn<MenuItem, String> currencyColumn = new TableColumn<>("Currency");
            currencyColumn.setCellValueFactory(new PropertyValueFactory<>("moneda"));

            tableView.getColumns().addAll(itemColumn, priceColumn, currencyColumn);
            tableView.getItems().addAll(items);
            tableView.setOnMouseClicked(event -> {
                if (event.getClickCount() == 2) {
                    MenuItem clickedItem = tableView.getSelectionModel().getSelectedItem();
                    if (clickedItem != null) {
                        if (selectedItems.contains(clickedItem)) {
                            selectedItems.remove(clickedItem);
                            System.out.println("Removed: " + clickedItem.getItem());
                        } else {
                            selectedItems.add(clickedItem);
                            System.out.println("Added: " + clickedItem.getItem());
                        }
                    }
                }
            });
            tableContainer.getChildren().add(categoryLabel);
            tableContainer.getChildren().add(tableView);
        }
    }
     */
}
