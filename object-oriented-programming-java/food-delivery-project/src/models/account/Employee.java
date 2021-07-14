package models.account;

import models.misc.Location;

import java.util.Arrays;

public class Employee extends Account {
    private Location location;
    private int salary;
    private boolean status;

    public Employee(String username, String email, String password, String phoneNumber, Location location, int salary) {
        super(username, email, password, phoneNumber);
        this.salary = salary;
        this.location = new Location(location);
        this.status = false;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return (true);
        }

        if (obj == null || getClass() != obj.getClass()) {
            return (false);
        }

        Employee other = (Employee) obj;
        return (this.username.equals(other.username) && this.email.equals(other.email) && this.location.equals(other.location));
    }

    @Override
    public String toString() {
        return (String.join("\n", Arrays.asList("ID: " + this.localId, "Username: " + this.username, "Email: " + this.email, "phoneNumber: " + this.phoneNumber, "Location: " + this.location.toString(), "Salary: " + salary)));
    }

    public Location getLocation() {
        return location;
    }

    public void setLocation(Location location) {
        this.location = new Location(location);
    }

    public int getSalary() {
        return salary;
    }

    public void setSalary(int salary) {
        this.salary = salary;
    }

    public void switchStatus() {
        this.status = !this.status;



    }
}
