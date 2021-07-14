package cli_menu.user;

import cli_menu.Menu;
import models.account.User;
import models.restaurant.Order;
import models.restaurant.Restaurant;
import services.restaurant.RestaurantService;
import state.AppState;

import java.io.IOException;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

public class OrderMenu extends Menu {
    public OrderMenu(AppState currentState) {
        this.currentState = currentState;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);
        RestaurantService restaurantService = this.currentState.getRestaurantService();
        List<Restaurant> restaurantList = restaurantService.getAll();

        int choice = -1;
        while (choice < 0 || choice > restaurantList.size() + 1) {
            System.out.println("Select a restaurant: ");

            for (int i = 0; i < restaurantList.size(); i++) {
                Restaurant restaurant = restaurantList.get(i);
                System.out.println(i + ". " + restaurant.getName());
            }

            System.out.println(restaurantList.size() + ". " + "Exit this menu.");
            choice = scanner.nextInt();
        }

        User user = (User) this.currentState.getCurrentUser();
        if (choice < restaurantList.size() - 1) {
            Restaurant restaurant = restaurantList.get(choice);
            if (restaurant.getCategories().size() == 0) {
                System.out.println("This restaurant doesn't have any categories.");
            } else {
                this.currentState.changeMenu(new OrderMenuCategories(currentState, restaurant, new Order(new Date(), user.getLocation(), restaurant)));
            }
        } else if (choice == restaurantList.size()) {
            this.currentState.popMenu();
        }
    }
}
