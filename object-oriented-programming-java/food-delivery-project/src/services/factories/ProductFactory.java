package services.factories;

import models.restaurant.Product;
import services.database.CSVLogger;

import java.io.IOException;
import java.util.Scanner;

public class ProductFactory {
    private static ProductFactory productFactory = null;

    private ProductFactory() {
    }

    public static ProductFactory getInstance() {
        if (productFactory == null)
            productFactory = new ProductFactory();

        return productFactory;
    }

    public Product createProductCLI() throws IOException {
        Scanner scanner = new Scanner(System.in);
        String name = null;
        int price = -1;

        while (name == null || !validateName(name)) {
            System.out.println("Enter a valid product name: ");
            name = scanner.nextLine();
        }

        while (price < 0) {
            System.out.println(("Enter a valid price: "));
            price = scanner.nextInt();
        }

//        CSVLogger.getInstance().writeAction(String.format("Product created - %s", name));
        return new Product(name, price);
    }

    protected boolean validateName(String name) {
        return name.matches("^[a-zA-Z0-9_-]{3,64}$");
    }
}