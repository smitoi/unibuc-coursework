package models.restaurant;

import services.database.DatabaseConfig;

import java.sql.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Category {
    private String name;
    private List<Product> products;

    public Category(String name) {
        this.name = name;
        this.products = new ArrayList<>();
    }

    public Category(Category obj) {
        this.name = obj.name;
        this.products = new ArrayList<>();
        obj.products.forEach((object) -> this.products.add(new Product(object)));
    }

    public void addProduct(Product product, boolean saveDatabase) {
        products.add(new Product(product));

        int category_id = -1;

        if (saveDatabase) {
            try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

                String query = "SELECT * FROM categories WHERE name = ?";

                PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                preparedStatement.setString(1, this.getName());
                ResultSet resultSet = preparedStatement.executeQuery();

                resultSet.next();

                category_id = resultSet.getInt(1);

            } catch (SQLException exception) {
                throw new RuntimeException("Something went wrong while tying to get the category id.");
            }

            try (Connection connection = DatabaseConfig.getDatabaseConnection()) {
                String query = "INSERT INTO pao_lab.products (name, price, category_id) VALUES (?, ?, ?)";

                PreparedStatement preparedStatement = connection.prepareStatement(query);
                preparedStatement.setString(1, product.getName());
                preparedStatement.setInt(2, product.getPrice());
                preparedStatement.setInt(3, category_id);

                preparedStatement.execute();

            } catch (SQLException exception) {
                throw new RuntimeException("Something went wrong while tying to add a new product.");
            }
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return (true);
        }

        if (obj == null || getClass() != obj.getClass()) {
            return (false);
        }

        Category other = (Category) obj;
        return (this.name.equals(other.name) &&
                this.products.equals(other.products));
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.name, this.products);
    }

    @Override
    public String toString() {
        return (String.join("\n", Arrays.asList("Name: " + this.name,
                "Products: " + products.toString())));
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<Product> getProducts() {
        return products;
    }

    public void setProducts(List<Product> products) {
        this.products = products;
    }
}
