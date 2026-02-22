module curs.practic {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires javafx.base;

    opens curs.practic to javafx.fxml;
    exports curs.practic;
    exports curs.practic.Controllers;
    opens curs.practic.Controllers to javafx.fxml;
}