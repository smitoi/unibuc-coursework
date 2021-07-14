
# Aplicație de Food Delivery
## Proiect pentru cursul de Programare Avansată pe Obiecte

#### Descrierea aplicației
Aplicația de food delivery realizată în Java, utilizând concepte de OOP și design patterns. În momentul actual utilizează rulează doar în consolă.

#### Etapa I:
* 1. Cel puțin 8 clase principale:
```java
Order

Restaurant
Category
Product

Admin
Employee
Partner
User

Location
```

* 2. Cel puțin 10 interogări / acțiuni:
```java

RestaurantService
    addOne(key, obj), getOne(key, index), getAll(), getAll(key), delete(key, index), remove(key, obj)
OrderService
    addOne(key, obj), getOne(key, index), getAll(), getAll(key), delete(key, index), remove(key, obj)
LoginService
    loginUser()
RegisterService
    registerUser(), validateInput()
Menu
    UserMenu
    OrderMenu
    PartnerMenu
    ModifyCategoryMenu
    ModifyRestaurantMenu
```

* 3. Cel puțin 2 colecții diferite:
```java
    // Repository.java, 8
    Map<K, List<T>> repoList;

    // AppState.java, 18
    Stack<Menu> menuStack;

    // Category.java, 10
    List<Product> products;
```

* 4. Utilizare moștenire pentru crearea de clase adiționale:
```java
public class Partner extends Account
public class User extends Account
public class UserMenu extends Menu
```

* 5. O clasă main din care sunt făcute apeluri către servicii
```java
// App.java
public class App

// AppState.java
public class AppState
```

#### Etapa II:
* 1. Persistență prin utilizare de fișiere:
```java
// CSVWriter.java
public class CSVWriter {
	public void writeRestaurantData();
	public void writeUserData();
}

// CSVReader.java
public class CSVReader {
	public Map<Partner, List<Restaurant>> readRestaurants();
	public List<Account> readUsers();
}

// Fișierele .csv sunt în /src/services/database/csv/
// La începutul programului se încarcă automat datele prin RestaurantService, respectiv AuthService
// Când se finalizează programul AppState se ocupă de apelarea CSVWriter pentru a rescrie datele.
```
* 2. Serviciu de audit:
```java
// CSVLogger.java
public class CSVLogger {
	public void writeAction(String action);
}

// Va crea un log pentru fiecare rulare a aplicației.
```
#### Etapa III:
* Înlocuiți serviciile realizate în etapa a II-a cu servicii care sa asigure persistenta utilizând baza de date folosind JDBC. 

* Să se realizeze servicii care sa expună operații de tip create, read, update si delete pentru cel puțin 4 dintre clasele definite. 

```java
// DatabaseConfig.java - clasa ce implementează conexiunea cu baza de date
public class DatabaseConfig {
    public static Connection getDatabaseConnection() throws SQLException { ... }
}

// Am implementat operațiuni de tipul CRUD pentru următoarele entități: Users (toate tipurile), Restaurants, Products, Categories.
// De asemenea, citesc din baza de date Orders
```