package scs.utilities.database;

import scs.utilities.errors.DatabaseException;
import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

import java.sql.Connection;
import java.sql.SQLException;

public final class Db {

    private static HikariDataSource DATA_SOURCE;

    private Db() {
    }

    public static synchronized void setGlobalConnection(String url, String username, String password) {
        if (DATA_SOURCE == null) {
            HikariConfig config = new HikariConfig();
            config.setJdbcUrl(url);
            config.setUsername(username);
            config.setPassword(password);

            config.setMaximumPoolSize(10);
            config.setMinimumIdle(2);
            config.setIdleTimeout(30000);

            DATA_SOURCE = new HikariDataSource(config);
        }
    }

    public static Connection getConnection() throws SQLException {
        if (DATA_SOURCE == null)
            throw new DatabaseException("connection", "Database not initialized yet.");

        return DATA_SOURCE.getConnection();
    }

    public static void close() {
        if (DATA_SOURCE != null)
            DATA_SOURCE.close();
    }
}
