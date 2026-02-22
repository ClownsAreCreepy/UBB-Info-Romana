open module scs {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.graphics;

    requires java.sql;
    requires org.postgresql.jdbc;
    requires com.zaxxer.hikari;

    requires org.slf4j.simple;
//    requires jbcrypt;

    exports scs;
}