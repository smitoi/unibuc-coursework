package cli_menu.auth;

import cli_menu.admin.AdminMenu;
import cli_menu.partner.PartnerMenu;
import models.account.*;
import cli_menu.Menu;
import cli_menu.user.UserMenu;
import state.AppState;

import java.io.IOException;
import java.util.Scanner;

public class AuthMenu extends Menu {
    public AuthMenu(AppState currentState) {
        this.currentState = currentState;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println(this.currentState);
        int choice = -1;
        while (choice < 1 || choice > 3) {
            System.out.println("Welcome to delivery2.io. You are currently not logged in, do you want to:" +
                    "\n1. Register as a new user." +
                    "\n2. Login as an existing user." +
                    "\n3. Exit the application.");
            choice = scanner.nextInt();
        }

        Account user;

        switch (choice) {
            case 1:
                user = this.currentState.getAuthService().registerNewUser();
                this.currentState.setCurrentUser(user);

                this.currentState.pushMenu(new UserMenu(currentState));
                break;
            case 2:
                user = this.currentState.getAuthService().loginUser();
                this.currentState.setCurrentUser(user);

                if (user instanceof User) {
                    currentState.pushMenu(new UserMenu(currentState));
                } else if (user instanceof Employee) {
                    // currentState.pushMenu(new DriverMenu(currentState));
                } else if (user instanceof Admin) {
                    currentState.pushMenu(new AdminMenu(currentState));
                } else if (user instanceof Partner) {
                    currentState.pushMenu(new PartnerMenu(currentState));
                }
                break;
            case 3:
            default:
                currentState.popMenu();
                System.out.println("Leaving the application...");
        }
    }
}