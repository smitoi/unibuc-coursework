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

public class SelectRestaurantMenu extends Menu {
    private final String action;

    public SelectRestaurantMenu(AppState currentState, String action) {
        this.currentState = currentState;
        this.action = action;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);
        Partner partner = (Partner) this.currentState.getCurrentUser();
        RestaurantService restaurantService = this.currentState.getRestaurantService();
        List<Restaurant> restaurants = restaurantService.getAll(partner);

        int choice = -1;
        if (restaurants.size() == 0) {
            System.out.println("You have not added any restaurants yet.");
            this.currentState.popMenu();
        } else {
            int i = 0;

            for (Restaurant restaurant : restaurants) {
                System.out.println(i + ". " + restaurant.toString());
                i += 1;
            }

            while (choice < 0 || choice >= restaurants.size()) {
                System.out.println("Select the restaurant you want to " + this.action + ": ");
                choice = scanner.nextInt();
            }
        }

        Restaurant restaurant = restaurantService.getOne(partner, choice);
        if (this.action.equals("update")) {
            this.currentState.changeMenu(new UpdateRestaurantMenu(currentState, restaurant));
        } else if (this.action.equals("modify")) {
            RestaurantFactory restaurantFactory = this.currentState.getRestaurantFactory();
            Restaurant newRestaurant = restaurantFactory.createRestaurantCLI((Partner)this.currentState.getCurrentUser(), false);
            restaurantService.updateRestaurant(restaurant, newRestaurant);
            restaurant.setName(newRestaurant.getName());
            restaurant.setLocation(newRestaurant.getLocation());
            this.currentState.popMenu();
        } else {
            restaurantService.delete(partner, choice);
            restaurantService.deleteRestaurant(restaurant);
            this.currentState.popMenu();
        }
    }
}