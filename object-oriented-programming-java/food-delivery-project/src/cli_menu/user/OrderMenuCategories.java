package cli_menu.user;

import cli_menu.Menu;
import models.account.User;
import models.restaurant.Category;
import models.restaurant.Order;
import models.restaurant.Product;
import models.restaurant.Restaurant;
import services.database.CSVLogger;
import services.database.DatabaseConfig;
import services.restaurant.OrderService;
import state.AppState;

import java.io.IOException;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.Scanner;

public class OrderMenuCategories extends Menu {
    final private Restaurant restaurant;
    final private Order order;

    public OrderMenuCategories(AppState currentState, Restaurant restaurant, Order order) {
        this.currentState = currentState;
        this.restaurant = restaurant;
        this.order = order;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);

        int choice = -1;
        while (choice < 0 || choice > restaurant.getCategories().size() + 1) {
            System.out.println("Select a category: ");
            for (int i = 0; i < restaurant.getCategories().size(); i++) {
                System.out.println(i + ". " + restaurant.getCategories().get(i).getName());
            }

            System.out.println(this.restaurant.getCategories().size() + ". " + "Exit this menu and place current order.");
            choice = scanner.nextInt();
        }

        OrderService orderService = this.currentState.getOrdersService();
        if (choice < this.restaurant.getCategories().size()) {
            Category category = this.restaurant.getCategories().get(choice);
            this.currentState.pushMenu(new OrderMenuProducts(this.currentState, category, order));
        } else if (choice == this.restaurant.getCategories().size()) {
            if (this.order.getProducts().size() != 0) {
                User user = (User) this.currentState.getCurrentUser();
//                CSVLogger.getInstance().writeAction(String.format("User add one order - %s", user.getUsername()));
                System.out.println("Added order");
                orderService.addOrder(this.order, user);
            } else {
                System.out.println("You didn't select any products!");
            }
            this.currentState.popMenu();
        }
    }
}
