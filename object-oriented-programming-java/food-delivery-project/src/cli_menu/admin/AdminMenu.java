package cli_menu.admin;

import cli_menu.Menu;
import models.account.Employee;
import state.AppState;

import java.io.IOException;
import java.util.Scanner;

public class AdminMenu extends Menu {
    public AdminMenu(AppState currentState) {
        this.currentState = currentState;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);

        int choice = -1;
        while (choice < 1 || choice > 3) {
            System.out.println("Welcome to delivery2.io. You are currently logged in as " + this.currentState.getCurrentUser().getUsername() +
                    "\n1. Add a new driver account." +
                    "\n2. Add a new partner account." +
                    "\n3. Log out.");
            choice = scanner.nextInt();
        }

        switch (choice) {
            case 1:
                this.currentState.getAuthService().registerNewDriver();
                break;
            case 2:
                this.currentState.getAuthService().registerNewPartner();
                break;
            case 3:
            default:
                System.out.println("Logging out...");
                this.currentState.popMenu();
                break;
        }
    }
}