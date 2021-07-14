package models.restaurant;

import java.util.Arrays;
import java.util.Objects;

public class Product {
    private String name;
    private int price;

    public Product(String name, int price) {
        this.name = name;
        this.price = price;
    }

    public Product(Product obj) {
        this.name = obj.getName();
        this.price = obj.getPrice();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return (true);
        }

        if (obj == null || getClass() != obj.getClass()) {
            return (false);
        }

        Product other = (Product) obj;
        return (this.name.equals(other.name) &&
                (this.price == other.price));
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.name, this.price);
    }

    @Override
    public String toString() {
        return (String.join("\n", Arrays.asList("Name: " + this.name, "Price: " + this.price)));
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
