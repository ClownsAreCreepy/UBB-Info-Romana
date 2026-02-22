open module scs {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires jbcrypt;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;
    requires org.postgresql.jdbc;
    requires com.zaxxer.hikari;
    requires javafx.graphics;
    requires org.slf4j.simple;

    exports scs;
}