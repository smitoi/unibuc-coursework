package cli_menu.partner;

import cli_menu.Menu;
import models.restaurant.Category;
import models.restaurant.Restaurant;
import services.factories.CategoryFactory;
import state.AppState;

import java.io.IOException;
import java.util.Scanner;

public class UpdateRestaurantMenu extends Menu {
    Restaurant restaurant;

    public UpdateRestaurantMenu(AppState currentState, Restaurant restaurant) {
        this.currentState = currentState;
        this.restaurant = restaurant;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println(this.currentState);
        int choice = -1;
        while (choice < 1 || choice > 6) {
            System.out.println("You have selected restaurant " + this.restaurant.getName() +
                    "\n1. Add a new category." +
                    "\n2. Modify a category." +
                    "\n3. Delete a category." +
                    "\n4. Add a new product." +
                    "\n5. Modify a product." +
                    "\n6. Delete a product." +
                    "\n7. Cancel.");
            choice = scanner.nextInt();
        }

        switch (choice) {
            case 1:
                CategoryFactory categoryFactory = this.currentState.getCategoryFactory();
                Category category = categoryFactory.createCategoryCLI();
                this.restaurant.addCategory(category, true);
                this.currentState.popMenu();
                break;
            case 2:
                this.currentState.changeMenu(new SelectCategoryMenu(currentState, restaurant, "modify category"));
                break;
            case 3:
                this.currentState.changeMenu(new SelectCategoryMenu(currentState, restaurant, "delete category"));
                break;
            case 4:
                this.currentState.changeMenu(new SelectCategoryMenu(currentState, restaurant, "add product"));
                break;
            case 5:
                this.currentState.changeMenu(new SelectCategoryMenu(currentState, restaurant, "modify product"));
                break;
            case 6:
                this.currentState.changeMenu(new SelectCategoryMenu(currentState, restaurant, "delete product"));
                break;
            case 7:
            default:
                this.currentState.popMenu();
                break;
        }
    }
}