package models.restaurant;

import models.misc.Location;

import java.util.*;

public class Order {
    private static int globalId = 1;

    private int localId;
    private int restaurantId;
    private String restaurantName;
    private Date date;
    private Location location;
    private List<Product> products;


    public Order(Date date, Location location, Restaurant restaurant) {
        this.localId = globalId;
        this.date = (Date) date.clone();
        this.location = new Location(location);
        this.products = new ArrayList<>();
        this.restaurantId = restaurant.getLocalId();
        this.restaurantName = restaurant.getName();
        globalId++;
    }

    public Order(Order obj) {
        System.out.println(obj);
        this.localId = obj.getLocalId();
        this.date = (Date) obj.getDate().clone();
        this.location = new Location(obj.getLocation());
        this.restaurantId = obj.restaurantId;
        this.restaurantName = obj.restaurantName;
        obj.products.forEach((object) -> this.products.add(new Product(object)));
    }

    public void addProduct(Product obj) {
        this.products.add(new Product(obj));
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return (true);
        }

        if (obj == null || getClass() != obj.getClass()) {
            return (false);
        }

        Order other = (Order) obj;
        return (this.date.equals(other.date) &&
                this.location.equals(other.location) &&
                this.products.equals((other.products)));
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.localId, this.date, this.location);
    }

    @Override
    public String toString() {
        return (String.join("\n", Arrays.asList("ID: " + this.localId,
                "Date: " + this.date,
                "Location: " + this.location,
                "Restaurant: " + this.restaurantName + "(" + this.restaurantId + ")",
                "Products: " + this.products)));
    }

    public int getLocalId() {
        return localId;
    }

    public void setLocalId(int localId) {
        this.localId = localId;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = (Date) date.clone();
    }

    public Location getLocation() {
        return location;
    }

    public void setLocation(Location location) {
        this.location = location;
    }

    public List<Product> getProducts() {
        return products;
    }

    public void setProducts(List<Product> products) {
        this.products = products;
    }

    public int getRestaurantId() {
        return restaurantId;
    }

    public void setRestaurantId(int restaurantId) {
        this.restaurantId = restaurantId;
    }

    public String getRestaurantName() {
        return restaurantName;
    }
}
