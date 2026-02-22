package scs.ui.controllers.logins;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import scs.domain.user.User;
import scs.service.social.UserService;
import scs.ui.controllers.logins.LoginController.LoginAction;

import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import scs.utilities.errors.ValidationException;

import java.io.IOException;
import java.time.LocalDate;

public class SignUpController {
    @FXML
    private ComboBox<String> typeSelector;
    @FXML
    private TextField usernameField;
    @FXML
    private TextField emailField;
    @FXML
    private PasswordField passHidden;
    @FXML
    private TextField passText;

    @FXML
    private VBox personFields;
    @FXML
    private TextField firstNameField;
    @FXML
    private TextField lastNameField;
    @FXML
    private TextField jobField;
    @FXML
    private DatePicker birthDate;

    @FXML
    private VBox duckFields;
    @FXML
    private TextField speedField;
    @FXML
    private TextField resistanceField;
    @FXML
    private ComboBox<String> duckSpeciesSelector;

    @FXML
    private Label errorLabel;

    private UserService userService;
    private LoginAction onLoginSuccess;

    public void setService(UserService service, LoginAction action) {
        this.userService = service;
        this.onLoginSuccess = action;
    }

    @FXML
    public void initialize() {
        typeSelector.setOnAction(e -> {
            boolean isPerson = typeSelector.getValue().equals("Person");

            personFields.setVisible(isPerson);
            personFields.setManaged(isPerson);

            duckFields.setVisible(!isPerson);
            duckFields.setManaged(!isPerson);
        });

        passHidden.textProperty().bindBidirectional(passText.textProperty());
    }

    @FXML
    public void onRegister() {
        try {
            String username = usernameField.getText();
            String email = emailField.getText();
            String pass = passHidden.getText();
            String type = typeSelector.getValue();

            User newUser;

            if (type.equals("Person")) {
                String first = firstNameField.getText();
                String last = lastNameField.getText();
                String job = jobField.getText();
                LocalDate dob = birthDate.getValue();

                newUser = userService.createPerson(username, email, pass, last, first, dob, job);
            } else {
                double speed = Double.parseDouble(speedField.getText());
                double res = Double.parseDouble(resistanceField.getText());
                String species = duckSpeciesSelector.getValue();

                if (species == null)
                    throw new ValidationException("duck type", "Please select a species");

                newUser = switch (species) {
                    case "SWIMMING" -> userService.createSwimmingDuck(username, email, pass, speed, res);
                    case "FLYING" -> userService.createFlyingDuck(username, email, pass, speed, res);
                    default -> userService.createHybridDuck(username, email, pass, speed, res);
                };
            }

            if (onLoginSuccess != null)
                onLoginSuccess.onLogin(newUser);
        } catch (NumberFormatException e) {
            errorLabel.setText("Speed and Resistance must be a valid number.");
            errorLabel.setVisible(true);
        } catch (Exception e) {
            errorLabel.setText("Error: " + e.getMessage());
            errorLabel.setVisible(true);
        }
    }

    @FXML
    public void onTogglePassword() {
        boolean show = !passHidden.isVisible();

        passHidden.setVisible(show);
        passHidden.setManaged(show);

        passText.setVisible(!show);
        passText.setManaged(!show);
    }

    @FXML
    public void onGoToLogin() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/scs/side-views/logins/login-view.fxml"));
            Parent root = loader.load();

            LoginController ctrl = loader.getController();
            ctrl.setService(userService, onLoginSuccess);

            usernameField.getScene().setRoot(root);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
