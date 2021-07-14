package cli_menu.user;

import cli_menu.Menu;
import models.account.User;
import models.restaurant.Order;
import services.restaurant.OrderService;
import state.AppState;

import java.io.IOException;
import java.util.List;
import java.util.Scanner;

public class UserMenu extends Menu {
    public UserMenu(AppState currentState) {
        this.currentState = currentState;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);

        int choice = -1;
        while (choice < 1 || choice > 3) {
            System.out.println("Welcome to delivery2.io. You are currently logged in as " + this.currentState.getCurrentUser().getUsername() +
                    "\n1. Place a new order." +
                    "\n2. Display your orders (this session only)." +
                    "\n3. Log out.");
            choice = scanner.nextInt();
        }

        switch (choice) {
            case 1:
                this.currentState.pushMenu(new OrderMenu(currentState));
                break;
            case 2:
                User user = (User) this.currentState.getCurrentUser();
                OrderService orderService = this.currentState.getOrdersService();
                List<Order> orders = orderService.getAll(user);
                if (orders == null || orders.size() == 0) {
                    System.out.println("You have not added any orders yet.");
                } else {
                    for (Order order : orders) {
                        System.out.println(order);
                    }
                }
                break;
            case 3:
            default:
                System.out.println("Logging out...");
                this.currentState.popMenu();
                break;
        }
    }
}