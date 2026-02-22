package scs.ui.controllers.logins;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleButton;
import scs.domain.user.User;
import scs.service.social.UserService;

import java.io.IOException;

public class LoginController {
    @FXML
    private TextField emailField;
    @FXML
    private PasswordField passHiddenField;
    @FXML
    private TextField passTextField;
    @FXML
    private ToggleButton togglePassBtn;
    @FXML
    private Label errorLabel;

    private UserService userService;
    private LoginAction onLoginSuccess;

    public interface LoginAction {
        void onLogin(User user);
    }

    public void setService(UserService service, LoginAction action) {
        this.userService = service;
        this.onLoginSuccess = action;

        passHiddenField.textProperty().bindBidirectional(passTextField.textProperty());
    }

    @FXML
    public void onLogin() {
        String email = emailField.getText();
        String pass = passHiddenField.getText();

        try {
            User user = userService.login(email, pass);
            errorLabel.setVisible(false);

            if (onLoginSuccess != null)
                onLoginSuccess.onLogin(user);
        } catch (Exception e) {
            errorLabel.setText(e.getMessage());
            errorLabel.setVisible(true);
            // System.out.println(e.getMessage());
        }
    }

    @FXML
    public void onTogglePassword() {
        boolean show = togglePassBtn.isSelected();

        passHiddenField.setVisible(!show);
        passHiddenField.setManaged(!show);

        passTextField.setVisible(show);
        passTextField.setManaged(show);
    }

    @FXML
    public void onGoToSignUp() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/scs/side-views/logins/signup-view.fxml"));
            Parent root = loader.load();

            SignUpController ctrl = loader.getController();
            ctrl.setService(userService, onLoginSuccess);

            emailField.getScene().setRoot(root);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
