package services.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class DatabaseConfig {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/pao_lab";
    private static final String USER = "root";
    private static final String PASSWORD = "";

    private static Connection databaseConnection;

    private static DatabaseConfig databaseConfig = null;

    private DatabaseConfig() {
        try {
            Properties connectionProps = new Properties();
            connectionProps.put("user", DatabaseConfig.USER);
            connectionProps.put("password", DatabaseConfig.PASSWORD);

            databaseConnection = DriverManager.getConnection(DB_URL, connectionProps);
        }

        catch (SQLException exception) {
            throw new RuntimeException("Couldn't initialize the connection: " + exception);
        }
    }

    public static DatabaseConfig getInstance() {
        if (databaseConfig == null)
            databaseConfig = new DatabaseConfig();

        return databaseConfig;
    }

    public static Connection getDatabaseConnection() throws SQLException {
        if (databaseConnection.isClosed()) {
            try {
                Properties connectionProps = new Properties();
                connectionProps.put("user", DatabaseConfig.USER);
                connectionProps.put("password", DatabaseConfig.PASSWORD);

                databaseConnection = DriverManager.getConnection(DB_URL, connectionProps);
            }

            catch (SQLException exception) {
                throw new RuntimeException("Couldn't initialize the connection: " + exception);
            }
        }
        return databaseConnection;
    }
}