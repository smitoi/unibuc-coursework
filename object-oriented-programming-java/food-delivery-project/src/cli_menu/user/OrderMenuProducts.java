package cli_menu.user;

import cli_menu.Menu;
import models.restaurant.Category;
import models.restaurant.Order;
import models.restaurant.Product;
import state.AppState;

import java.io.IOException;
import java.util.Scanner;

public class OrderMenuProducts extends Menu {
    final private Category category;
    final private Order order;

    public OrderMenuProducts(AppState currentState, Category category, Order order) {
        this.currentState = currentState;
        this.category = category;
        this.order = order;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println(this.currentState);
        int choice = -1;

        while (choice < 0 || choice > category.getProducts().size() + 1) {
            System.out.println("Select a product: ");
            for (int i = 0; i < category.getProducts().size(); i++) {
                System.out.println(i + ". " + category.getProducts().get(i).getName());
            }

            System.out.println(this.category.getProducts().size() + ". " + "Exit this menu.");
            choice = scanner.nextInt();
        }


        if (choice < this.category.getProducts().size()) {
            Product product = this.category.getProducts().get(choice);
            this.order.addProduct(new Product(product));
        }

        this.currentState.popMenu();
    }
}