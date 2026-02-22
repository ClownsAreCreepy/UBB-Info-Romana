package scs.ui;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import scs.domain.User;
import scs.service.CarService;

import java.io.IOException;
import java.util.function.Consumer;

public class WindowManager {
    public static <T> void openWindow(String fxml, String title, Consumer<T> setup) {
        try {
            FXMLLoader loader = new FXMLLoader(WindowManager.class.getResource(fxml));
            Parent root = loader.load();
            T ctrl = loader.getController();
            if (setup != null) setup.accept(ctrl);

            Stage stage = new Stage();
            stage.setTitle(title);
            stage.setScene(new Scene(root));

            stage.setOnHidden(e -> {
                if (ctrl instanceof DashboardController)
                    ((DashboardController) ctrl).close();
            });

            stage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void openDashboard(CarService carService, User user) {
        openWindow("/scs/dashboard-view.fxml",
                "App - " + user.getUsername(),
                (DashboardController ctrl) -> {
                    ctrl.setService(carService, user);
                });
    }
}
/*

    // 3. Login Window
    public static void openLogin() {
        openWindow("/scs/login-view.fxml", "Login",
                   (LoginController ctrl) -> ctrl.setServices());
    }
 */