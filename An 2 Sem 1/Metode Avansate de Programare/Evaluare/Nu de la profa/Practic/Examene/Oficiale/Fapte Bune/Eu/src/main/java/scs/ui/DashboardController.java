package scs.ui;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import scs.domain.Entity;
import scs.domain.Nevoie;
import scs.domain.Persoana;
import scs.service.GenericService;
import scs.service.NevoieService;
import scs.service.PersoanaService;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observer;

import java.time.LocalDateTime;
import java.time.LocalTime;

public class DashboardController implements Observer<EntityChangeEvent<Nevoie>> {
    @FXML private TableView<Nevoie> nevoiOrasTable;
    @FXML private TableColumn<Nevoie, String> colTitluOras;
    @FXML private TableColumn<Nevoie, String> colDescriereOras;
    @FXML private TableColumn<Nevoie, LocalDateTime> colDeadlineOras;
    @FXML private TableColumn<Nevoie, String> colStatusOras;

    @FXML private TableView<Nevoie> fapteBuneTable;
    @FXML private TableColumn<Nevoie, String> colTitluFapte;
    @FXML private TableColumn<Nevoie, String> colDescriereFapte;
    @FXML private TableColumn<Nevoie, LocalDateTime> colDeadlineFapte;
    @FXML private TableColumn<Nevoie, String> colStatusFapte;

    @FXML private TextField titluNevoieField;
    @FXML private TextArea descriereNevoieField;
    @FXML private DatePicker deadlinePicker;

    private NevoieService nevoieService;
    private PersoanaService persoanaService;
    private Persoana loggedInUser;

    private ObservableList<Nevoie> modelNevoiOras = FXCollections.observableArrayList();
    private ObservableList<Nevoie> modelFapteBune = FXCollections.observableArrayList();

    public void setService(NevoieService nevoieService, PersoanaService persoanaService, Persoana loggedInUser) {
        this.nevoieService = nevoieService;
        this.persoanaService = persoanaService;
        this.loggedInUser = loggedInUser;

        this.nevoieService.addObserver(this);

        initTables();
        loadData();
    }

    private void initTables() {
        colTitluOras.setCellValueFactory(new PropertyValueFactory<>("titlu"));
        colDescriereOras.setCellValueFactory(new PropertyValueFactory<>("descriere"));
        colDeadlineOras.setCellValueFactory(new PropertyValueFactory<>("deadline"));
        colStatusOras.setCellValueFactory(new PropertyValueFactory<>("status"));
        nevoiOrasTable.setItems(modelNevoiOras);

        colTitluFapte.setCellValueFactory(new PropertyValueFactory<>("titlu"));
        colDescriereFapte.setCellValueFactory(new PropertyValueFactory<>("descriere"));
        colDeadlineFapte.setCellValueFactory(new PropertyValueFactory<>("deadline"));
        colStatusFapte.setCellValueFactory(new PropertyValueFactory<>("status"));
        fapteBuneTable.setItems(modelFapteBune);
    }

    private void loadData() {
        modelNevoiOras.setAll(nevoieService.getNevoiPentruOras(loggedInUser.getOras(), loggedInUser.getId()));
        modelFapteBune.setAll(nevoieService.getFapteBune(loggedInUser.getId()));
    }

    @FXML public void handlePreiaNevoie() {
        Nevoie selected = nevoiOrasTable.getSelectionModel().getSelectedItem();
        if (selected == null) {
            showAlert("Eroare", "Selectati o nevoie pentru a o prelua!");
            return;
        }

        if (selected.getStatus().equals("Erou gasit!")) {
            showAlert("Eroare", "Aceasta nevoie si-a gasit deja un erou!");
            return;
        }

        try {
            nevoieService.preiaNevoie(selected.getId(), loggedInUser.getId());
            showAlert("Success", "Nevoia ti-a fost atribuita!");
        } catch (Exception e) {
            showAlert("Eroare", e.getMessage());
        }
    }

    @FXML public void handleAdaugaNevoie() {
        try {
            if (deadlinePicker.getValue() == null) {
                throw new RuntimeException("Selectati un deadline!");
            }

            LocalDateTime deadline = LocalDateTime.of(deadlinePicker.getValue(), LocalTime.of(23, 59));

            Nevoie n = new Nevoie(
                    null,
                    titluNevoieField.getText(),
                    descriereNevoieField.getText(),
                    deadline,
                    loggedInUser.getId(),
                    null,
                    "Caut erou!"
            );

            nevoieService.add(n);
            showAlert("Success", "Nevoia tia fost adaugata!");

            titluNevoieField.clear();
            descriereNevoieField.clear();
            deadlinePicker.setValue(null);
        } catch (Exception e) {
            showAlert("Eroare", e.getMessage());
        }
    }

    @Override
    public void update(EntityChangeEvent<Nevoie> event) {
        Platform.runLater(() -> {
            loadData();
        });
    }

    private void showAlert(String title, String message) {
        Alert a = new Alert(Alert.AlertType.INFORMATION);
        a.setTitle(title);
        a.setContentText(message);
        a.show();
    }

    public void close() { nevoieService.removeObserver(this); }
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