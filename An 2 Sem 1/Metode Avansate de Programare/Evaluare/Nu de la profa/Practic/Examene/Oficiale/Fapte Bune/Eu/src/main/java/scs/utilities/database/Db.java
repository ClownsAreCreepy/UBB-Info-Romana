package scs.utilities.database;

import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

import java.sql.Connection;
import java.sql.SQLException;

public class Db {
    private static HikariDataSource DATA_SOURCE;

    public static synchronized void setGlobalConnection(String url, String username, String password) {
        if (DATA_SOURCE == null) {
            HikariConfig config = new HikariConfig();
            config.setJdbcUrl(url);
            config.setUsername(username);
            config.setPassword(password);
            DATA_SOURCE = new HikariDataSource(config);
        }
    }

    public static Connection getConnection() throws SQLException {
        return DATA_SOURCE.getConnection();
    }
}