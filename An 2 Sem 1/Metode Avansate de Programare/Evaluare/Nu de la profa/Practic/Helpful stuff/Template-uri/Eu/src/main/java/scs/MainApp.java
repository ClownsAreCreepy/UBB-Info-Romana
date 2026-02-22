package scs;

import javafx.application.Application;
import javafx.stage.Stage;
import scs.utilities.database.Db;
import scs.ui.WindowManager;
// import your.domain.*;

public class MainApp extends Application {
    @Override
    public void start(Stage stage) {
        // 1. DB
        Db.setGlobalConnection(System.getenv("DB_URL"), System.getenv("DB_USER"), System.getenv("DB_PASSWORD"));

        // 2. Repos & Services
        // var repo = new CarRepository();
        // var service = new GenericService<>(repo);

        // 3. Open Windows (Window per User)
        // service.getAllUsers().forEach(u -> WindowManager.openWindow(..., ctrl -> ctrl.setService(service, u)));

        // Or Single Window
        WindowManager.openWindow("/scs/dashboard-view.fxml", "Main", null);
    }
    public static void main(String[] args) { launch(args); }
}