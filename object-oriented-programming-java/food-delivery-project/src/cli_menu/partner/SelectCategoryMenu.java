package cli_menu.partner;

import cli_menu.Menu;
import models.restaurant.Category;
import models.restaurant.Restaurant;
import services.database.DatabaseConfig;
import state.AppState;

import java.io.IOException;
import java.sql.*;
import java.util.Scanner;

public class SelectCategoryMenu extends Menu {
    private final Restaurant restaurant;
    private final String action;

    public SelectCategoryMenu(AppState currentState, Restaurant restaurant, String action) {
        this.currentState = currentState;
        this.restaurant = restaurant;
        this.action = action;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);

        int choice = -1;
        if (this.restaurant.getCategories().size() == 0) {
            System.out.println("This restaurant doesn't have any categories.");
        } else {
            int i = 0;
            for (Category category : this.restaurant.getCategories()) {
                System.out.println(i + ". " + category);
                i += 1;
            }

            while (choice < 0 || choice > this.restaurant.getCategories().size()) {
                System.out.println("Select the category you want to " + action + " for  " + this.restaurant.getName());
                choice = scanner.nextInt();
            }
        }

        if (choice != -1) {
            if (action.equals("delete category")) {
                this.restaurant.removeCategory(choice);
                this.currentState.popMenu();
            } else if (action.equals("modify category")) {
                this.restaurant.updateCategory(choice);
                this.currentState.popMenu();
            }
            else {
                this.currentState.changeMenu(new ModifyCategoryMenu(this.currentState, this.restaurant.getCategories().get(choice), action));
            }
        } else {
            this.currentState.popMenu();
        }
    }
}