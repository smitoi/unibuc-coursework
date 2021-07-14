package services.factories;


import models.restaurant.Category;
import services.database.CSVLogger;

import java.io.IOException;
import java.util.Scanner;

public class CategoryFactory {
    private static CategoryFactory categoryFactory = null;

    private CategoryFactory() { }

    public static CategoryFactory getInstance() {
        if (categoryFactory == null)
            categoryFactory = new CategoryFactory();

        return categoryFactory;
    }

    public Category createCategoryCLI() throws IOException {
        Scanner scanner = new Scanner(System.in);
        String name = null;

        while (name == null || !validateName(name)) {
            System.out.println("Enter a valid category name: ");
            name = scanner.nextLine();
        }

//        CSVLogger.getInstance().writeAction(String.format("Category created - %s", name));
        return new Category(name);
    }

    protected boolean validateName(String name) {
        return name.matches("^[a-zA-Z0-9_-]{3,16}$");
    }
}