package scs;

import javafx.application.Application;
import javafx.stage.Stage;
import scs.repo.NevoieRepository;
import scs.repo.PersoanaRepository;
import scs.service.NevoieService;
import scs.service.PersoanaService;
import scs.ui.LoginController;
import scs.ui.WindowManager;
import scs.utilities.database.Db;
// import your.domain.*;

public class MainApp extends Application {
    @Override
    public void start(Stage stage) {
        // 1. DB
        Db.setGlobalConnection(System.getenv("DB_URL"), System.getenv("DB_USER"), System.getenv("DB_PASSWORD"));

        PersoanaRepository persoanaRepository = new PersoanaRepository();
        NevoieRepository nevoieRepository = new NevoieRepository();

        PersoanaService persoanaService = new PersoanaService(persoanaRepository);
        NevoieService nevoieService = new NevoieService(nevoieRepository, persoanaRepository);

        // Or Single Window
        WindowManager.openWindow("/scs/login-view.fxml", "Fapte Bune - Login/Register",
                (LoginController ctrl) -> ctrl.setService(persoanaService, nevoieService));
    }
    public static void main(String[] args) { launch(args); }
}