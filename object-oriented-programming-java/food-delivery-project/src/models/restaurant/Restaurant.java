package models.restaurant;

import models.misc.Location;
import services.database.DatabaseConfig;
import services.factories.CategoryFactory;

import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Restaurant {
    private static int globalId = 1;

    private int localId;
    private String name;
    private Location location;
    private List<Category> categories;

    public Restaurant(String name, Location location) {
        this.localId = globalId;
        this.name = name;
        this.location = new Location(location);
        this.categories = new ArrayList<>();
        globalId++;
    }

    public Restaurant(Restaurant obj) {
        this.localId = obj.localId;
        this.name = obj.name;
        this.location = new Location(obj.location);
        obj.categories.forEach((object) -> this.categories.add(new Category(object)));
    }

    public void addCategory(Category category, boolean saveDatabase) {
        categories.add(new Category(category));

        int restaurant_id = -1;

        if (saveDatabase) {
            try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

                String query = "SELECT * FROM restaurants WHERE name = ? AND location_x = ? AND location_y = ?";

                PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                preparedStatement.setString(1, this.getName());
                preparedStatement.setDouble(2, this.getLocation().getX());
                preparedStatement.setDouble(3, this.getLocation().getY());
                ResultSet resultSet = preparedStatement.executeQuery();

                resultSet.next();

                restaurant_id = resultSet.getInt(1);

            } catch (SQLException exception) {
                throw new RuntimeException("Something went wrong while tying to get the restaurant id.");
            }

            try (Connection connection = DatabaseConfig.getDatabaseConnection()) {
                String query = "INSERT INTO pao_lab.categories (name, restaurant_id) VALUES (?, ?)";

                PreparedStatement preparedStatement = connection.prepareStatement(query);
                preparedStatement.setString(1, category.getName());
                preparedStatement.setInt(2, restaurant_id);

                preparedStatement.execute();

            } catch (SQLException exception) {
                throw new RuntimeException("Something went wrong while tying to add a new category.");
            }
        }
    }

    public void removeCategory(int index) {
        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

            String query = "DELETE FROM categories WHERE name = ?";

            PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, categories.get(index).getName());
            preparedStatement.execute();

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to delete the category.");
        }

        categories.remove(index);
    }

    public void updateCategory(int index) throws IOException {
        Category newCateogry = CategoryFactory.getInstance().createCategoryCLI();

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

            String query = "UPDATE categories SET name = ? WHERE name = ?";

            PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, newCateogry.getName());
            preparedStatement.setString(2, categories.get(index).getName());
            preparedStatement.execute();

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to update the category.");
        }

        categories.remove(index);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return (true);
        }

        if (obj == null || getClass() != obj.getClass()) {
            return (false);
        }

        Restaurant other = (Restaurant) obj;
        return ((this.localId == other.localId) &&
                this.name.equals(other.name) &&
                this.location.equals(other.location) &&
                this.categories.equals(other.categories));
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.name, this.localId);
    }

    @Override
    public String toString() {
        return (String.join("\n", Arrays.asList("ID: " + this.localId,
                "Name: " + this.name, "Location: " + this.location,
                "Categories: " + this.categories.toString())));
    }

    public int getLocalId() {
        return localId;
    }

    public void setLocalId(int localId) {
        this.localId = localId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Location getLocation() {
        return location;
    }

    public void setLocation(Location location) {
        this.location = location;
    }

    public List<Category> getCategories() {
        return categories;
    }

    public void setCategories(List<Category> categories) {
        this.categories = categories;
    }
}
