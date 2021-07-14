package cli_menu.driver;

import cli_menu.Menu;
import models.account.Employee;
import state.AppState;

import java.io.IOException;
import java.util.Scanner;

public class DriverMenu extends Menu {
    public DriverMenu(AppState currentState) {
        this.currentState = currentState;
    }

    public void handleMenu() throws IOException {
        Scanner scanner = new Scanner(System.in);

        int choice = -1;
        while (choice < 1 || choice > 2) {
            System.out.println("Welcome to delivery2.io. You are currently logged in as " + this.currentState.getCurrentUser().getUsername() +
                    "\n1. Change your status." +
                    "\n2. Log out.");
            choice = scanner.nextInt();
        }

        switch (choice) {
            case 1:
                Employee employee = (Employee) this.currentState.getCurrentUser();
                employee.switchStatus();
                break;
            case 2:
            default:
                System.out.println("Logging out...");
                this.currentState.popMenu();
                break;
        }
    }
}