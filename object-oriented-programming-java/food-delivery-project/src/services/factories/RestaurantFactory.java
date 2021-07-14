package services.factories;


import models.account.Partner;
import models.misc.Location;
import models.restaurant.Restaurant;
import services.database.CSVLogger;
import services.database.DatabaseConfig;

import java.io.IOException;
import java.sql.*;
import java.util.Scanner;

public class RestaurantFactory {
    private static RestaurantFactory restaurantFactory = null;

    private RestaurantFactory() { }

    public static RestaurantFactory getInstance() {
        if (restaurantFactory == null)
            restaurantFactory = new RestaurantFactory();

        return restaurantFactory;
    }

    public Restaurant createRestaurantCLI(Partner partner, boolean saveDatabase) throws IOException {
        int owner_id = -1;

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

            String query = "SELECT id FROM accounts WHERE username = ?";

            PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, partner.getUsername());
            ResultSet resultSet = preparedStatement.executeQuery();

            resultSet.next();

            owner_id = resultSet.getInt(1);

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to get the owner id.");
        }

        Scanner scanner = new Scanner(System.in);

        double x = 10 + Math.random() * (90 - 10);
        double y = 10 + Math.random() * (90 - 10);

        Location location = new Location(x, y);

        String name = null;

        while (name == null || !validateName(name)) {
            System.out.println("Enter a valid restaurant name: ");
            name = scanner.nextLine();
        }

//        CSVLogger.getInstance().writeAction(String.format("Restaurant created - %s", name));
        if (saveDatabase) {
            try (Connection connection = DatabaseConfig.getDatabaseConnection()) {
                String query = "INSERT INTO pao_lab.restaurants (name, location_x, location_y, owner_id) VALUES (?, ?, ?, ?)";

                PreparedStatement preparedStatement = connection.prepareStatement(query);
                preparedStatement.setString(1, name);
                preparedStatement.setDouble(2, location.getX());
                preparedStatement.setDouble(3, location.getY());
                preparedStatement.setInt(4, owner_id);

                preparedStatement.execute();

            } catch (SQLException exception) {
                throw new RuntimeException("Something went wrong while tying to add a new restaurant.");
            }
        }

        return new Restaurant(name, location);
    }

    protected boolean validateName(String name) {
        return name.matches("^[a-zA-Z0-9_-]{3,64}$");
    }
}