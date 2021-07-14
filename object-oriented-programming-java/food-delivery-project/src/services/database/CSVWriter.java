package services.database;

import models.account.*;
import models.restaurant.Category;
import models.restaurant.Product;
import models.restaurant.Restaurant;
import services.auth.AuthService;
import services.restaurant.RestaurantService;

import java.io.FileWriter;
import java.io.IOException;

public class CSVWriter {
    private static CSVWriter csvWriter = null;

    private CSVWriter() { }

    public static CSVWriter getInstance() {
        if (csvWriter == null)
            csvWriter = new CSVWriter();

        return csvWriter;
    }

    public void writeRestaurantData() throws IOException {
        RestaurantService restaurantService = RestaurantService.getInstance();

        FileWriter restaurantWriter = new FileWriter("./src/services/database/csv/restaurant.csv");
        FileWriter productWriter = new FileWriter("./src/services/database/csv/product.csv");
        FileWriter categoryWriter = new FileWriter("./src/services/database/csv/category.csv");

        restaurantWriter.write("id,name,location_x,location_y\n");
        productWriter.write("nume_restaurant,nume_categorie,nume_produs,preț\n");
        categoryWriter.write("nume_restaurant,nume_categorie\n");

        for (Restaurant res : restaurantService.getAll()) {
            restaurantWriter.write(String.format("%d,%s,%f,%f\n", res.getLocalId(), res.getName(), res.getLocation().getX(), res.getLocation().getY()));

            for (Category cat : res.getCategories()) {
                categoryWriter.write(String.format("%s,%s\n", res.getName(), cat.getName()));

                for (Product prod : cat.getProducts()) {
                    productWriter.write(String.format("%s,%s,%s,%d\n", res.getName(), cat.getName(), prod.getName(), prod.getPrice()));

                }
            }
        }

        restaurantWriter.close();
        categoryWriter.close();
        productWriter.close();
    }

    public void writeUserData() throws IOException {
        AuthService authService = AuthService.getInstance();

        FileWriter adminWriter = new FileWriter("./src/services/database/csv/admin.csv");
        FileWriter userWriter = new FileWriter("./src/services/database/csv/user.csv");
        FileWriter employeeWriter = new FileWriter("./src/services/database/csv/employee.csv");
        FileWriter partnerWriter = new FileWriter("./src/services/database/csv/partner.csv");

        partnerWriter.write("id_user,username,email,parola,numar_telefon,firma\n");
        employeeWriter.write("id_user,username,email,parola,numar_telefon,locatie_x,locatie_y,salariu\n");
        adminWriter.write("id_user,username,email,parola,numar_telefon\n");
        userWriter.write("id_user,username,email,parola,numar_telefon,locatie_x,locatie_y\n");

        for (Account account : authService.getRegisteredAccounts()) {
            if (account instanceof User) {
                User user = (User) account;
                userWriter.append(String.format("%s,%s,%s,%s,%s,%s,%s\n", user.getLocalId(), user.getUsername(), user.getEmail(), user.getPassword(), user.getPhoneNumber(), user.getLocation().getX(), user.getLocation().getY()));
            } else if (account instanceof Employee) {
                Employee employee = (Employee) account;
                employeeWriter.append(String.format("%s,%s,%s,%s,%s,%s,%s,%s\n", employee.getLocalId(), employee.getUsername(), employee.getEmail(), employee.getPassword(), employee.getPhoneNumber(), employee.getLocation().getX(), employee.getLocation().getY(), employee.getSalary()));
            } else if (account instanceof Admin) {
                Admin admin = (Admin) account;
                adminWriter.append(String.format("%s,%s,%s,%s,%s\n", admin.getLocalId(), admin.getUsername(), admin.getEmail(), admin.getPassword(), admin.getPhoneNumber()));
            } else if (account instanceof Partner) {
                Partner partner = (Partner) account;
                partnerWriter.append(String.format("%s,%s,%s,%s,%s,%s\n", partner.getLocalId(), partner.getUsername(), partner.getEmail(), partner.getPassword(), partner.getPhoneNumber(), partner.getFirmName()));
            }
        }

        userWriter.close();
        adminWriter.close();
        employeeWriter.close();
        partnerWriter.close();
    }
}
