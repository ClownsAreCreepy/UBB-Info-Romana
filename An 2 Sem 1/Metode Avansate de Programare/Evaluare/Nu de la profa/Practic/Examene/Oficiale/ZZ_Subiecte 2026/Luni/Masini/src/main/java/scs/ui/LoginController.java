package scs.ui;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import scs.domain.User;
import scs.service.CarService;
import scs.service.UserService;

public class LoginController {
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;
    @FXML
    private Label errorLabel;

    private UserService userService;
    private CarService carService;

    public void setServices(UserService userService, CarService carService) {
        this.userService = userService;
        this.carService = carService;
    }

    @FXML
    public void onLogin() {
        String username = usernameField.getText();
        String password = passwordField.getText();

        User loggedUser = userService.login(username, password);

        if (loggedUser == null)
            errorLabel.setText("Wrong credentials");
        else
            WindowManager.openDashboard(carService, loggedUser);
    }
}
