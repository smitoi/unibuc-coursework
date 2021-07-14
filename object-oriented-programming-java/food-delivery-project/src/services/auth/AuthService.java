package services.auth;

import models.account.*;
import models.misc.Location;
import services.database.DatabaseConfig;

import java.io.IOException;
import java.sql.*;
import java.util.List;
import java.util.Scanner;

public class AuthService {
    private List<Account> registeredAccounts;
    private static AuthService authService = null;

    private AuthService() {
        // this.registeredAccounts = registeredAccounts;
    }

    public static AuthService getInstance() throws IOException {
        if (authService == null)
            authService = new AuthService();

        return authService;
    }

    private static Account mapToAccount(ResultSet resultSet) throws SQLException {
        Account account = null;

        switch (resultSet.getString(9)) {
            case "admin":
                account = new Admin(resultSet.getString(1), resultSet.getString(2), resultSet.getString(3), resultSet.getString(4));
                break;
            case "employee":
                account = new Employee(resultSet.getString(1), resultSet.getString(2), resultSet.getString(3), resultSet.getString(4), new Location(resultSet.getFloat(6), resultSet.getFloat(7)), resultSet.getInt(8));
                break;
            case "partner":
                account = new Partner(resultSet.getString(1), resultSet.getString(2), resultSet.getString(3), resultSet.getString(4), resultSet.getString(5));
                break;
            case "user":
                account = new User(resultSet.getString(1), resultSet.getString(2), resultSet.getString(3), resultSet.getString(4), new Location(resultSet.getFloat(6), resultSet.getFloat(7)));
                break;
        }

        return account;
    }

//    private static List<Account> getRegisteredUsers() throws IOException {
//         return CSVReader.getInstance().readUsers();
//    }

    private boolean validatePhoneNumber(String phone) {
        return phone.matches("^(07)[0-9]{8}$");
    }

    private boolean validateUsername(String name) {
        return name.matches("^[a-zA-Z0-9_-]{3,16}$");
    }

    private boolean validateFirmname(String name) {
        return name.matches("^[a-zA-Z0-9_-]{3,16}$");
    }

    private boolean validatePassword(String pass) {
        return pass.matches("^[a-zA-Z0-9_-]{6,24}$");
    }

    private boolean validateEmail(String email) {
        return email.matches("^(.+){5,64}@(.+){5,64}$");
    }

    public List<Account> getRegisteredAccounts() {
        return registeredAccounts;
    }

    public Account loginUser() throws IOException {
        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

            Scanner scanner = new Scanner(System.in);
            Account request = new Account();

            String username = null;
            String password = null;

            while (username == null || !validateUsername(username)) {
                System.out.println("Enter a valid username: ");
                username = scanner.nextLine();

                String query = "SELECT * FROM accounts WHERE username = ?";

                PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                preparedStatement.setString(1, username);

                ResultSet resultSet = preparedStatement.executeQuery();

                if (!resultSet.next()) {
                    System.out.println("This username is not taken by any user!");
                    return null;
                }
            }

            while (password == null || !validatePassword(password)) {
                System.out.println("Enter a valid password: ");
                password = scanner.nextLine();
            }

            request.setUsername(username);
            request.setPassword(password);

            String query = "SELECT * FROM accounts WHERE username = ? AND password = ?";

            PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, request.getUsername());
            preparedStatement.setString(2, request.getPassword());

            ResultSet resultSet = preparedStatement.executeQuery();

            if (!resultSet.next()) {
                System.out.println("Wrong username or password");
                return null;
            } else {
                final String type = resultSet.getString(10);

                switch (type) {
                    case "user":
                        return new User(resultSet.getString(2),
                                resultSet.getString(3),
                                resultSet.getString(4),
                                resultSet.getString(5),
                                new Location(resultSet.getFloat(7), resultSet.getFloat(7)));
                    case "admin":
                        return new Admin(resultSet.getString(2),
                                resultSet.getString(3),
                                resultSet.getString(4),
                                resultSet.getString(5));
                    case "employee":
                        return new Employee(resultSet.getString(2),
                                resultSet.getString(3),
                                resultSet.getString(4),
                                resultSet.getString(5),
                                new Location(resultSet.getFloat(7), resultSet.getFloat(8)),
                                resultSet.getInt(9));
                    case "partner":
                        return new Partner(resultSet.getString(2),
                                resultSet.getString(3),
                                resultSet.getString(4),
                                resultSet.getString(5),
                                resultSet.getString(6));
                }
            }
        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to log in.");
        }

        return null;
    }

    public Account registerInputValidationUser() {
        Scanner scanner = new Scanner(System.in);
        String username = null;
        String password = null;
        String email = null;
        String phoneNumber = null;

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {
            while (username == null || !validateUsername(username)) {
                System.out.println("Enter a valid username: ");
                username = scanner.nextLine();

                String query = "SELECT * FROM accounts WHERE username = ?";

                PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                preparedStatement.setString(1, username);

                ResultSet resultSet = preparedStatement.executeQuery();

                if (resultSet.next()) {
                    System.out.println("This username is already taken by another user!");
                    username = null;
                }
            }

            while (email == null || !validateEmail(email)) {
                System.out.println("Enter a valid email: ");
                email = scanner.nextLine();

                String query = "SELECT * FROM accounts WHERE email = ?";

                PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                preparedStatement.setString(1, email);

                preparedStatement.execute();
                ResultSet resultSet = preparedStatement.getGeneratedKeys();

                if (resultSet.next()) {
                    System.out.println("This email is already taken by another user!");
                    email = null;
                }
            }


        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to validate the data.");
        }

        while (password == null || !validatePassword(password)) {
            System.out.println("Enter a valid password: ");
            password = scanner.nextLine();
        }

        while (phoneNumber == null || !validatePhoneNumber(phoneNumber)) {
            System.out.println("Enter a valid phone number: ");
            phoneNumber = scanner.nextLine();
        }

        return new Account(username, email, password, phoneNumber);
    }

    public User registerNewUser() throws IOException {

        double x = 10 + Math.random() * (90 - 10);
        double y = 10 + Math.random() * (90 - 10);

        Location location = new Location(x, y);

        Account account = registerInputValidationUser();

        User user = new User(account.getUsername(), account.getEmail(), account.getPassword(), account.getPhoneNumber(), location);

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {
            String query = "INSERT INTO pao_lab.accounts (username, email, password, phone_number, location_x, location_y, type) VALUES (?, ?, ?, ?, ?, ?, ?)";

            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, user.getUsername());
            preparedStatement.setString(2, user.getEmail());
            preparedStatement.setString(3, user.getPassword());
            preparedStatement.setString(4, user.getPhoneNumber());
            preparedStatement.setDouble(5, user.getLocation().getX());
            preparedStatement.setDouble(6, user.getLocation().getY());
            preparedStatement.setString(7, "user");

            preparedStatement.execute();

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to register.");
        }

        return user;
    }

    public Partner registerInputValidationPartner() {
        Scanner scanner = new Scanner(System.in);
        String username = "Partner_";
        String password = null;
        String email = null;
        String phoneNumber = null;
        String firmName = null;

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {
            try {
                String query = "SELECT MAX(id) FROM accounts";

                PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                ResultSet resultSet = preparedStatement.executeQuery();

                resultSet.next();
                username = username + resultSet.getInt(1);
            } finally {
                while (email == null || !validateEmail(email)) {
                    System.out.println("Enter a valid email: ");
                    email = scanner.nextLine();

                    String query = "SELECT * FROM accounts WHERE email = ?";

                    PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                    preparedStatement.setString(1, email);

                    preparedStatement.execute();
                    ResultSet resultSet = preparedStatement.getGeneratedKeys();

                    if (resultSet.next()) {
                        System.out.println("This email is already taken by another user!");
                        email = null;
                    }
                }
            }
        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to validate the data.");
        }

        while (password == null || !validatePassword(password)) {
            System.out.println("Enter a valid password: ");
            password = scanner.nextLine();
        }

        while (phoneNumber == null || !validatePhoneNumber(phoneNumber)) {
            System.out.println("Enter a valid phone number: ");
            phoneNumber = scanner.nextLine();
        }

        while (firmName == null || !validateFirmname(firmName)) {
            System.out.println("Enter a valid firm name: ");
            firmName = scanner.nextLine();
        }

        return new Partner(username, email, password, phoneNumber, firmName);
    }

    public void registerNewPartner() throws IOException {

        Partner partner = registerInputValidationPartner();

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {
            String query = "INSERT INTO pao_lab.accounts (username, email, password, phone_number, firm_name, type) VALUES (?, ?, ?, ?, ?, ?)";

            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, partner.getUsername());
            preparedStatement.setString(2, partner.getEmail());
            preparedStatement.setString(3, partner.getPassword());
            preparedStatement.setString(4, partner.getPhoneNumber());
            preparedStatement.setString(5, partner.getFirmName());
            preparedStatement.setString(6, "partner");

            preparedStatement.execute();

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to register.");
        }

    }

    public Employee registerInputValidationDriver() {
        Scanner scanner = new Scanner(System.in);
        String username = "Driver_";
        String password = null;
        String email = null;
        String phoneNumber = null;
        String salary = null;

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {

            try {
                String query = "SELECT MAX(id) FROM accounts";

                PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                ResultSet resultSet = preparedStatement.executeQuery();

                resultSet.next();
                username = username + resultSet.getInt(1);
            } finally {
                while (email == null || !validateEmail(email)) {
                    System.out.println("Enter a valid email: ");
                    email = scanner.nextLine();

                    String query = "SELECT * FROM accounts WHERE email = ?";

                    PreparedStatement preparedStatement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
                    preparedStatement.setString(1, email);

                    preparedStatement.execute();
                    ResultSet resultSet = preparedStatement.getGeneratedKeys();

                    if (resultSet.next()) {
                        System.out.println("This email is already taken by another user!");
                        email = null;
                    }
                }
            }
        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to validate the data.");
        }

        while (password == null || !validatePassword(password)) {
            System.out.println("Enter a valid password: ");
            password = scanner.nextLine();
        }

        while (phoneNumber == null || !validatePhoneNumber(phoneNumber)) {
            System.out.println("Enter a valid phone number: ");
            phoneNumber = scanner.nextLine();
        }

        while (salary == null || Integer.parseInt(salary) < 0) {
            System.out.println("Enter a valid salary: ");
            salary = scanner.nextLine();
        }

        double x = 10 + Math.random() * (90 - 10);
        double y = 10 + Math.random() * (90 - 10);

        Location location = new Location(x, y);

        return new Employee(username, email, password, phoneNumber, location, Integer.parseInt(salary));
    }

    public void registerNewDriver() throws IOException {

        Employee employee = registerInputValidationDriver();

        try (Connection connection = DatabaseConfig.getDatabaseConnection()) {
            String query = "INSERT INTO pao_lab.accounts (username, email, password, phone_number, location_x, location_y, salary, type) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, employee.getUsername());
            preparedStatement.setString(2, employee.getEmail());
            preparedStatement.setString(3, employee.getPassword());
            preparedStatement.setString(4, employee.getPhoneNumber());
            preparedStatement.setDouble(5, employee.getLocation().getX());
            preparedStatement.setDouble(6, employee.getLocation().getY());
            preparedStatement.setInt(7, employee.getSalary());
            preparedStatement.setString(8, "employee");

            preparedStatement.execute();

        } catch (SQLException exception) {
            throw new RuntimeException("Something went wrong while tying to register.");
        }

    }
}
