package scs.ui;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

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
            stage.show();
        } catch (Exception e) { e.printStackTrace(); }
    }
}

/*
// open Dashboard for a User
    public static void openDashboard(User user) {
        openWindow("/scs/trader.fxml",
                   "App - " + user.getUsername(),
                   (DashboardController ctrl) -> {
                       ctrl.setService(context.getGenericService(), user);
                   });
    }

    // login Window
    public static void openLogin() {
        openWindow("/scs/login-view.fxml", "Login",
                   (LoginController ctrl) -> ctrl.setContext(context));
    }
 */