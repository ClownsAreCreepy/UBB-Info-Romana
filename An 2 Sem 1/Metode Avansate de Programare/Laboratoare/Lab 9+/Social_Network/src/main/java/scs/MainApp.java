package scs;

import scs.domain.user.User;
import scs.ui.controllers.logins.LoginController;
import scs.ui.MainController;
import scs.app.AppContext;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.Parent;

import java.io.IOException;

public class MainApp extends Application {
    private Stage loginStage;
    private AppContext ctx;

    @Override
    public void start(Stage stage) {
        this.loginStage = stage;
        this.ctx = new AppContext();

        initLogin();
    }

    public void initLogin() {
        try {
            FXMLLoader loader = new FXMLLoader(MainApp.class.getResource("/scs/side-views/logins/login-view.fxml"));
            Parent root = loader.load();

            LoginController ctrl = loader.getController();

            ctrl.setService(ctx.PGUserService, this::initMainDashboard);

            loginStage.setScene(new Scene(root));
            loginStage.setTitle("Duck Social - Login");

            loginStage.setWidth(400);
            loginStage.setHeight(640);
            // loginStage.centerOnScreen();
            loginStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void initMainDashboard(User user) {
        try {
            Stage dashboardStage = new Stage();

            FXMLLoader loader = new FXMLLoader(MainApp.class.getResource("/scs/main-view.fxml"));
            Parent root = loader.load();

            MainController ctrl = loader.getController();

            Runnable onLogout = () -> {
                ctrl.cleanup();
                dashboardStage.close();
                initLogin();
            };

            ctrl.setContext(ctx, user, onLogout);

            dashboardStage.setScene(new Scene(root));
            dashboardStage.setTitle("Duck Social - " + user.getUsername());

            dashboardStage.setOnHidden(e -> ctrl.cleanup());

            dashboardStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch();
    }
}

