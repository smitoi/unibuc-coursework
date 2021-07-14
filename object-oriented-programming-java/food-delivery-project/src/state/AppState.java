package state;

import models.account.Account;
import services.auth.AuthService;
import cli_menu.Menu;
import cli_menu.auth.AuthMenu;
import services.database.CSVLogger;
import services.database.CSVReader;
import services.database.CSVWriter;
import services.database.DatabaseConfig;
import services.factories.CategoryFactory;
import services.factories.ProductFactory;
import services.factories.RestaurantFactory;
import services.restaurant.OrderService;
import services.restaurant.RestaurantService;

import java.io.IOException;
import java.util.Stack;

public class AppState {
    private Account currentUser;
    private final Stack<Menu> menuStack;

    private final DatabaseConfig databaseConfig = DatabaseConfig.getInstance();

    // Services
    private final AuthService authService = AuthService.getInstance();
    private final RestaurantService restaurantService = RestaurantService.getInstance();
    private final OrderService orderService = OrderService.getInstance();

//    private final CSVReader csvReader = CSVReader.getInstance();
//    private final CSVWriter csvWriter = CSVWriter.getInstance();
//    private final CSVLogger csvLogger = CSVLogger.getInstance();

    // Factories
    private final RestaurantFactory restaurantFactory = RestaurantFactory.getInstance();
    private final CategoryFactory categoryFactory = CategoryFactory.getInstance();
    private final ProductFactory productFactory = ProductFactory.getInstance();

    public AppState() throws IOException {
        menuStack = new Stack<>();
        this.pushMenu(new AuthMenu(this));
    }

    public void execute() throws IOException {
        while (!menuStack.isEmpty()) {
            System.out.println(this.getCurrentMenu());
            this.getCurrentMenu().handleMenu();
        }
//        csvWriter.writeRestaurantData();
//        csvWriter.writeUserData();
//        csvLogger.getLogWriter().close();
    }

    public void pushMenu(Menu menu) throws IOException {
        this.menuStack.push(menu);
//        this.csvLogger.writeAction(String.format("Entered menu: %s", this.getCurrentMenu().getClass().getName()));
    }

    public Menu popMenu() throws IOException {
//        this.csvLogger.writeAction(String.format("Exited menu: %s", this.getCurrentMenu().getClass().getName()));
        return this.menuStack.pop();
    }

    public Menu changeMenu(Menu menu) {
        Menu ret = this.menuStack.pop();
        this.menuStack.push(menu);
        return ret;
    }

    public Menu getCurrentMenu() {
        return this.menuStack.peek();
    }

    public Account getCurrentUser() {
        return this.currentUser;
    }

    public void setCurrentUser(Account currentUser) {
        this.currentUser = currentUser;
    }

    public AuthService getAuthService() { return authService; }

    public RestaurantService getRestaurantService() {
        return this.restaurantService;
    }

    public OrderService getOrdersService() {
        return this.orderService;
    }

    public RestaurantFactory getRestaurantFactory() {
        return this.restaurantFactory;
    }

    public CategoryFactory getCategoryFactory() {
        return this.categoryFactory;
    }

    public ProductFactory getProductFactory() {
        return this.productFactory;
    }

}
