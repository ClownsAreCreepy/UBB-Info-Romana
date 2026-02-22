package scs.ui;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;
import scs.domain.Oras;
import scs.domain.Persoana;
import scs.service.NevoieService;
import scs.service.PersoanaService;

public class LoginController {
    @FXML private TextField numeField;
    @FXML private TextField prenumeField;
    @FXML private TextField usernameRegField;
    @FXML private PasswordField parolaField;
    @FXML private PasswordField parolaConfirmField;
    @FXML private ComboBox<Oras> orasComboBox;
    @FXML private TextField stradaField;
    @FXML private TextField numar_stradaField;
    @FXML private TextField telefonField;

    @FXML private ListView<Persoana> usersListView;

    private PersoanaService persoanaService;
    private NevoieService nevoieService;

    public void setService(PersoanaService persoanaService, NevoieService nevoieService) {
        this.persoanaService = persoanaService;
        this.nevoieService = nevoieService;

        orasComboBox.setItems(FXCollections.observableArrayList(Oras.values()));

        loadUsers();
    }

    private void loadUsers() {
        usersListView.setItems(FXCollections.observableArrayList(persoanaService.getAll()));

        usersListView.setCellFactory(param -> new ListCell<>() {
            @Override
            protected void updateItem(Persoana user, boolean empty) {
                super.updateItem(user, empty);
                setText(empty || user == null ? null : user.getUsername());
            }
        });
    }

    @FXML private void handleRegister() {
        try{
            if (!parolaField.getText().equals(parolaConfirmField.getText())) {
                throw new RuntimeException("Parolele nu coincid!");
            }

            Persoana p = new Persoana(
                    null,
                    numeField.getText(),
                    prenumeField.getText(),
                    usernameRegField.getText(),
                    parolaField.getText(),
                    orasComboBox.getValue(),
                    stradaField.getText(),
                    numar_stradaField.getText(),
                    telefonField.getText()
            );

            persoanaService.add(p);
            showAlert("Success", "Inregistrare realizata cu success!");
            loadUsers();
        } catch (Exception e){
            showAlert("Eroare Inregistrare", e.getMessage());
        }
    }

    @FXML public void handleLogin() {
        Persoana selectedUser = usersListView.getSelectionModel().getSelectedItem();
        if (selectedUser == null) {
            showAlert("Eroare", "Selectati un utilizator din lista!");
            return;
        }

        openDashboard(selectedUser);
    }

    private void openDashboard(Persoana user) {
        WindowManager.openWindow("/scs/dashboard-view.fxml", "Dashboard - " + user.getUsername(),
                (DashboardController ctrl) -> ctrl.setService(nevoieService, persoanaService, user)
        );

        Stage stage = (Stage) usersListView.getScene().getWindow();
        stage.close();
    }

    private void showAlert(String title, String message) {
        Alert a = new Alert(Alert.AlertType.INFORMATION);
        a.setTitle(title);
        a.setContentText(message);
        a.show();
    }
}
