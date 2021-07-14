package services.restaurant;

import models.account.Partner;
import models.account.User;
import models.misc.Location;
import models.restaurant.Category;
import models.restaurant.Order;
import models.restaurant.Product;
import models.restaurant.Restaurant;
import services.database.DatabaseConfig;
import services.database.Repository;

import java.sql.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

public class OrderService extends Repository<User, Order> {
    private static OrderService orderService = null;

    private OrderService() {
        this.repoList = new HashMap();
    }

    public static OrderService getInstance() {
        if (orderService == null)
            orderService = new OrderService();

        return orderService;
    }

    public void addOrder(Order order, User user) {
        int order_id = -1;

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

            String queryUser = "SELECT id FROM accounts WHERE username = ?";
            PreparedStatement preparedStatementUser = connection.prepareStatement(queryUser);
            preparedStatementUser.setString(1, user.getUsername());
            ResultSet resultSetUser = preparedStatementUser.executeQuery();
            resultSetUser.next();
            int user_id = resultSetUser.getInt(1);

            String query = "INSERT INTO orders (issue_date, location_x, location_y, restaurant_name, user_id) VALUES (?, ?, ?, ?, ?)";

            String pattern = "yyyy-MM-dd";
            SimpleDateFormat formatter = new SimpleDateFormat(pattern);

            PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, formatter.format(order.getDate()));
            preparedStatement.setDouble(2, order.getLocation().getX());
            preparedStatement.setDouble(3, order.getLocation().getY());
            preparedStatement.setString(4, order.getRestaurantName());
            preparedStatement.setInt(5, user_id);
            preparedStatement.execute();
            ResultSet resultSet = preparedStatement.getGeneratedKeys();
            resultSet.next();

            order_id = resultSet.getInt(1);

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to create the order.");
        }

        for (Product product : order.getProducts()) {
            try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

                String queryProduct = "SELECT id FROM products WHERE name = ?";
                PreparedStatement preparedStatementProduct = connection.prepareStatement(queryProduct);
                preparedStatementProduct.setString(1, product.getName());
                ResultSet resultSetProduct = preparedStatementProduct.executeQuery();
                resultSetProduct.next();
                int product_id = resultSetProduct.getInt(1);

                String query = "INSERT INTO orders_products (order_id, product_id) VALUES (?, ?)";

                PreparedStatement preparedStatement = connection.prepareStatement(query);
                preparedStatement.setInt(1, order_id);
                preparedStatement.setInt(2, product_id);
                preparedStatement.execute();

            } catch (SQLException exception) {
                throw new RuntimeException("Something went wrong while tying to create the products for order.");
            }
        }

        this.addOne(user, order);
    }
}
