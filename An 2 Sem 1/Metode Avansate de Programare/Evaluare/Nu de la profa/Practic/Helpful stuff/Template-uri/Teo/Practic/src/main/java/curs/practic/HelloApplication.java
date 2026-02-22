package curs.practic;

import curs.practic.Controllers.AdminController;
import curs.practic.config.Config;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Properties;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Properties props = Config.getProperties();
        String dbUrl = props.getProperty("db.url");
        String dbUsername = props.getProperty("db.username");
        String dbPassword = props.getProperty("db.password");

//        DriverRepositoryInterface dri = new DriverDBRepository(dbUrl, dbUsername, dbPassword, new DriverValidator());
//        OrderRepositoryInterface ori = new OrderDBRepository(dbUrl, dbUsername, dbPassword, new OrderValidator());
//        Service s =  new Service(dri, ori);


        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("admin-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Admin");
        AdminController controller = fxmlLoader.getController();
//        controller.setService(s);
        stage.setScene(scene);
        stage.show();

    }
}
