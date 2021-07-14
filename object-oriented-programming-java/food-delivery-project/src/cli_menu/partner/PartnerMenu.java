package cli_menu.partner;

import cli_menu.Menu;
import models.account.Partner;
import models.restaurant.Restaurant;
import services.factories.RestaurantFactory;
import services.restaurant.RestaurantService;
import state.AppState;

import java.io.IOException;
import java.util.List;
import java.util.Scanner;

public class PartnerMenu extends Menu {
    public PartnerMenu(AppState currentState) {
        this.currentState = currentState;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);

        int choice = -1;
        while (choice < 1 || choice > 6) {
            System.out.println("Welcome to delivery2.io. You are currently logged in as " + this.currentState.getCurrentUser().getUsername() +
                    "\n1. See your restaurants." +
                    "\n2. Add a new restaurant." +
                    "\n3. Update a restaurant." +
                    "\n4. Delete a restaurant." +
                    "\n5. Modify a restaurant." +
                    "\n6. Log out.");
            choice = scanner.nextInt();
        }

        Partner partner = (Partner) this.currentState.getCurrentUser();
        RestaurantService restaurantService = this.currentState.getRestaurantService();
        List<Restaurant> restaurants = restaurantService.getAll(partner);
        switch (choice) {
            case (1): // See your restaurants
                if (restaurants == null || restaurants.size() == 0) {
                    System.out.println("You have not added any restaurants yet.");
                } else {
                    for (Restaurant restaurant : restaurants) {
                        System.out.println(restaurant);
                    }
                }
                break;
            case (2): // Add a new restaurant
                RestaurantFactory restaurantFactory = this.currentState.getRestaurantFactory();
                Restaurant restaurant = restaurantFactory.createRestaurantCLI((Partner)this.currentState.getCurrentUser(), true);
                restaurantService.addOne(partner, restaurant);
                break;
            case (3): // Update a restaurant
                this.currentState.pushMenu(new SelectRestaurantMenu(currentState, "update"));
                break;
            case (4): // Delete a restaurant
                this.currentState.pushMenu(new SelectRestaurantMenu(currentState, "delete"));
                break;
            case (5):
                this.currentState.pushMenu(new SelectRestaurantMenu(currentState, "modify"));
                break;
            case (6): // Log out
            default:
                System.out.println("Logging out...");
                this.currentState.popMenu();
                break;
        }
    }
}