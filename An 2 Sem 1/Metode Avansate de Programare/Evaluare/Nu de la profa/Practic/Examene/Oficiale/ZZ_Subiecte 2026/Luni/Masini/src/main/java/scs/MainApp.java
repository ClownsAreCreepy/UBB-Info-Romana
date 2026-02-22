package scs;

import javafx.application.Application;
import javafx.stage.Stage;
import scs.repo.CarRepository;
import scs.repo.UserRepository;
import scs.service.CarService;
import scs.service.UserService;
import scs.ui.LoginController;
import scs.utilities.database.Db;
import scs.ui.WindowManager;

public class MainApp extends Application {
    @Override
    public void start(Stage stage) {
        // 1. DB
        Db.setGlobalConnection(System.getenv("DB_URL"), System.getenv("DB_USER"), System.getenv("DB_PASSWORD"));

        // 2. Repos & Services
        UserRepository userRepo = new UserRepository();
        CarRepository carRepo = new CarRepository();

        UserService userService = new UserService(userRepo);
        CarService carService = new CarService(carRepo);

        // 3. Login Window
        WindowManager.openWindow("/scs/login-view.fxml", "Login",
                (LoginController ctrl) -> ctrl.setServices(userService, carService));
    }
    public static void main(String[] args) { launch(args); }
}
