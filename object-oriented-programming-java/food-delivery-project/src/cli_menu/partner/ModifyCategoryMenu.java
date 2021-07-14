package cli_menu.partner;

import cli_menu.Menu;
import models.restaurant.Category;
import models.restaurant.Product;
import services.database.DatabaseConfig;
import services.factories.CategoryFactory;
import services.factories.ProductFactory;
import state.AppState;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

public class ModifyCategoryMenu extends Menu {
    private final Category category;
    private final String action;

    public ModifyCategoryMenu(AppState currentState, Category category, String action) {
        this.currentState = currentState;
        this.category = category;
        this.action = action;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println(this.currentState);
        int choice = -1;

        if (action.equals("delete product") || action.equals("modify product")) {
            if (this.category.getProducts().size() == 0) {
                System.out.println("This category doesn't have any products.");
            } else {
                while (choice < 0 || choice > this.category.getProducts().size()) {
                    System.out.println("Select the product you want to " + action.split(" ")[0] + " - " + this.category.getName());
                    choice = scanner.nextInt();
                }
            }
            if (choice != -1 && action.equals("delete product")) {
                Product product = category.getProducts().get(choice);

                try (Connection connection = DatabaseConfig.getDatabaseConnection()) {
                    String query = "DELETE FROM pao_lab.products WHERE name = ? AND price = ?";

                    PreparedStatement preparedStatement = connection.prepareStatement(query);
                    preparedStatement.setString(1, product.getName());
                    preparedStatement.setInt(2, product.getPrice());

                    preparedStatement.execute();

                } catch (SQLException exception) {
                    throw new RuntimeException("Something went wrong while tying to delete a product.");
                }

                category.getProducts().remove(choice);
            } else if (choice != -1) {
                Product newProduct = this.currentState.getProductFactory().createProductCLI();
                Product product = category.getProducts().get(choice);

                try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

                    String query = "UPDATE products SET name = ?, price = ? WHERE name = ?";

                    PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                    preparedStatement.setString(1, newProduct.getName());
                    preparedStatement.setInt(2, newProduct.getPrice());
                    preparedStatement.setString(3, product.getName());
                    preparedStatement.execute();

                } catch (SQLException exception) {
                    throw new RuntimeException("Something went wrong while tying to update the product.");
                }
            }
        }

        ProductFactory productFactory = this.currentState.getProductFactory();
        if (action.equals("add product")) {
            Product product = productFactory.createProductCLI();
            this.category.addProduct(product, true);
        }

        this.currentState.popMenu();
    }
}