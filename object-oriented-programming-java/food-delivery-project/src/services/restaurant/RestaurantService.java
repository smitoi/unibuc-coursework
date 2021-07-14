package services.restaurant;

import models.account.Partner;
import models.misc.Location;
import models.restaurant.Category;
import models.restaurant.Product;
import models.restaurant.Restaurant;
import services.database.CSVReader;
import services.database.DatabaseConfig;
import services.database.Repository;

import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.HashMap;

public class RestaurantService extends Repository<Partner, Restaurant> {
    private static RestaurantService restaurantService = null;

    private RestaurantService() throws IOException {
         // this.repoList = CSVReader.getInstance().readRestaurants();
        this.repoList = new HashMap<>();

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

            String query = "SELECT * FROM restaurants";

            PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Restaurant restaurant = new Restaurant(resultSet.getString(2), new Location(resultSet.getDouble(3), resultSet.getDouble(4)));

                String queryCategory = "SELECT * FROM categories WHERE restaurant_id = ?";
                PreparedStatement preparedStatementCategory = connection.prepareStatement(queryCategory, Statement.RETURN_GENERATED_KEYS);
                preparedStatementCategory.setInt(1, resultSet.getInt(1));
                ResultSet resultSetCategory = preparedStatementCategory.executeQuery();
                while (resultSetCategory.next()) {
                    Category category = new Category(resultSetCategory.getString(2));

                    String queryProduct = "SELECT * FROM products WHERE category_id = ?";
                    PreparedStatement preparedStatementProduct = connection.prepareStatement(queryProduct, Statement.RETURN_GENERATED_KEYS);
                    preparedStatementProduct.setInt(1, resultSetCategory.getInt(1));
                    ResultSet resultSetProduct = preparedStatementProduct.executeQuery();

                    while (resultSetProduct.next()) {
                        Product product = new Product(resultSetProduct.getString(2), resultSetProduct.getInt(3));
                        category.addProduct(product, false);
                    }

                    restaurant.addCategory(category, false);
                }

                String queryPartner = "SELECT * FROM accounts WHERE id = ?";
                PreparedStatement preparedStatementPartner = connection.prepareStatement(queryPartner, Statement.RETURN_GENERATED_KEYS);
                preparedStatementPartner.setInt(1, resultSet.getInt(5));
                ResultSet resultSetPartner = preparedStatementPartner.executeQuery();
                resultSetPartner.next();

                Partner partner = new Partner(resultSetPartner.getString(2),
                        resultSetPartner.getString(3),
                        resultSetPartner.getString(4),
                        resultSetPartner.getString(5),
                        resultSetPartner.getString(6));

                if (this.repoList.get(partner) == null) {
                    this.repoList.put(partner, new ArrayList<>());
                }
                this.repoList.get(partner).add(restaurant);
            }

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to initialise the restaurants.");
        }

    }

    public static RestaurantService getInstance() throws IOException {
        if (restaurantService == null)
            restaurantService = new RestaurantService();

        return restaurantService;
    }

    public void updateRestaurant(Restaurant restaurant, Restaurant newRestaurant) {
        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

            String query = "UPDATE restaurants SET name = ?, location_x = ?, location_y = ? WHERE name = ? AND location_x = ? AND location_y = ?";

            PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, newRestaurant.getName());
            preparedStatement.setDouble(2, newRestaurant.getLocation().getX());
            preparedStatement.setDouble(3, newRestaurant.getLocation().getY());
            preparedStatement.setString(4, restaurant.getName());
            preparedStatement.setDouble(5, restaurant.getLocation().getX());
            preparedStatement.setDouble(6, restaurant.getLocation().getY());
            preparedStatement.execute();

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to update the restaurant.");
        }
    }

    public void deleteRestaurant(Restaurant restaurant) {
        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

            String query = "DELETE FROM restaurants WHERE name = ? AND location_x = ? AND location_y = ?";

            PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, restaurant.getName());
            preparedStatement.setDouble(2, restaurant.getLocation().getX());
            preparedStatement.setDouble(3, restaurant.getLocation().getY());
            preparedStatement.execute();

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to delete the restaurant.");
        }
    }

}
