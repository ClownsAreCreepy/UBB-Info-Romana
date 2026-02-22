package scs;

import javafx.application.Application;
import javafx.stage.Stage;
import scs.repo.CoinRepository;
import scs.repo.TransactionRepository;
import scs.repo.UserRepository;
import scs.service.MarketService;
import scs.service.MarketSimulator;
import scs.ui.AdminController;
import scs.ui.TraderController;
import scs.ui.WindowManager;
import scs.utilities.database.Db;
// import your.domain.*;

public class MainApp extends Application {

    private MarketSimulator simulator;

    @Override
    public void start(Stage stage) {
        // 1. DB
        Db.setGlobalConnection(System.getenv("DB_URL"), System.getenv("DB_USER"), System.getenv("DB_PASSWORD"));

        // 2. Repos & Services
        var userRepo = new UserRepository();
        var coinRepo = new CoinRepository();
        var transactionRepo = new TransactionRepository();
        var service = new MarketService(userRepo, coinRepo, transactionRepo);

        simulator = new MarketSimulator(service);
        Thread simThread = new Thread(simulator);
        simThread.setDaemon(true); // it dies if app crashes
        simThread.start();

        // 3. Open Windows (Window per User)
        service.getAllUsers().forEach(u -> WindowManager.openWindow("/scs/trader.fxml", "Trader: " + u.getName(), (TraderController ctrl) -> ctrl.setService(service, u)));

        // Or Single Window
        WindowManager.openWindow("/scs/admin.fxml", "Market Admin", (AdminController ctrl) -> ctrl.setService(service));
    }

    @Override
    public void stop() throws Exception {
        super.stop();
        if (simulator != null) {
            simulator.stop();
        }
    }

    public static void main(String[] args) { launch(args); }
}