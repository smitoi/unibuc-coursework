package models.account;

import models.misc.Location;

public class User extends Account {
    private Location location;

    public User(String username, String email, String password, String phoneNumber, Location location) {
        super(username, email, password, phoneNumber);
        this.location = new Location(location);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return (true);
        }

        if (obj == null || getClass() != obj.getClass()) {
            return (false);
        }

        User other = (User) obj;
        return (this.username.equals(other.username) && this.email.equals(other.email) && this.location.equals(other.location));
    }

    @Override
    public String toString() {
        return (super.toString() + '\n' + this.location.toString());
    }

    public Location getLocation() {
        return location;
    }

    public void setLocation(Location location) {
        this.location = new Location(location);
    }
}
