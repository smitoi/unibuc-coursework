package models.misc;

import java.util.Arrays;
import java.util.Objects;

public class Location {
    private double x;
    private double y;

    public Location(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Location(Location other) {
        this.x = other.getX();
        this.y = other.getY();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }

        Location other = (Location) obj;
        return (Double.compare(other.x, x) == 0 &&
                Double.compare(other.y, y) == 0);
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }

    @Override
    public String toString() {
        return (String.join("\n", Arrays.asList("X: " + this.x, "Y: " + this.y)));
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }
}
