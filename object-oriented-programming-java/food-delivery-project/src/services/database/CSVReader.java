package services.database;

import models.account.*;
import models.misc.Location;
import models.restaurant.Category;
import models.restaurant.Product;
import models.restaurant.Restaurant;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static java.lang.Float.parseFloat;
import static java.lang.Integer.parseInt;

public class CSVReader {
    private static CSVReader csvReader = null;

    private CSVReader() { }

    public static CSVReader getInstance() {
        if (csvReader == null)
            csvReader = new CSVReader();

        return csvReader;
    }

    public Map<Partner, List<Restaurant>> readRestaurants() throws IOException {
        Map<Partner, List<Restaurant>> restaurantRepo = new HashMap();
        restaurantRepo.put(null, new ArrayList<>());

        BufferedReader restaurantReader = new BufferedReader(new FileReader("./src/services/database/csv/restaurant.csv"));
        BufferedReader productReader = new BufferedReader(new FileReader("./src/services/database/csv/product.csv"));
        BufferedReader categoryReader = new BufferedReader(new FileReader("./src/services/database/csv/category.csv"));
        String row;

        // Citirea restaurantelor
        row = restaurantReader.readLine();
        System.out.println(row);
        while ((row = restaurantReader.readLine()) != null) {
            System.out.println(row);
            String[] data = row.split(",");
            Location location = new Location(parseFloat(data[2]), parseFloat(data[3]));
            Restaurant restaurant = new Restaurant(data[1], location);
            restaurant.setLocalId(parseInt(data[0]));
            restaurantRepo.get(null).add(restaurant);
        }

        // Adăugarea categoriilor
        row = categoryReader.readLine();
        System.out.println(row);
        while ((row = categoryReader.readLine()) != null) {
            System.out.println(row);
            String[] data = row.split(",");
            Category category = new Category(data[1]);
            for (Restaurant res : restaurantRepo.get(null)) {
                if (res.getName().equals(data[0])) {
                    res.addCategory(category, false);
                }
            }
        }

        // Adăugarea produselor
        row = productReader.readLine();
        System.out.println(row);
        while ((row = productReader.readLine()) != null) {
            System.out.println(row);
            String[] data = row.split(",");
            Product product = new Product(data[2], parseInt(data[3]));
            for (Restaurant res : restaurantRepo.get(null)) {
                if (res.getName().equals(data[0])) {
                    for (Category cat : res.getCategories()) {
                        if (cat.getName().equals(data[1])) {
                            cat.addProduct(product, false);
                        }
                    }
                }
            }
        }

        restaurantReader.close();
        categoryReader.close();
        productReader.close();

        return restaurantRepo;
    }

    public List<Account> readUsers() throws IOException {
        List<Account> usersList = new ArrayList();

        BufferedReader userReader = new BufferedReader(new FileReader("./src/services/database/csv/user.csv"));
        BufferedReader adminReader = new BufferedReader(new FileReader("./src/services/database/csv/admin.csv"));
        BufferedReader employeeReader = new BufferedReader(new FileReader("./src/services/database/csv/employee.csv"));
        BufferedReader partnerReader = new BufferedReader(new FileReader("./src/services/database/csv/partner.csv"));
        String row;

        // Citirea restaurantelor
        userReader.readLine();
        while ((row = userReader.readLine()) != null) {
            String[] data = row.split(",");
            usersList.add(new User(data[1], data[2], data[3], data[4], new Location(parseFloat(data[5]), parseFloat(data[6]))));
        }

        adminReader.readLine();
        while ((row = adminReader.readLine()) != null) {
            String[] data = row.split(",");
            usersList.add(new Admin(data[1], data[2], data[3], data[4]));
        }

        employeeReader.readLine();
        while ((row = employeeReader.readLine()) != null) {
            String[] data = row.split(",");
            usersList.add(new Employee(data[1], data[2], data[3], data[4], new Location(parseFloat(data[5]), parseFloat(data[6])), parseInt(data[7])));
        }

        partnerReader.readLine();
        while ((row = partnerReader.readLine()) != null) {
            String[] data = row.split(",");
            usersList.add(new Partner(data[1], data[2], data[3], data[4], data[5]));
        }

        userReader.close();
        adminReader.close();
        employeeReader.close();
        partnerReader.close();

        return usersList;
    }
}
