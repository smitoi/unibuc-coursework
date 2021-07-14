package models.account;

import java.util.Arrays;
import java.util.Objects;

public class Account {
    protected static int globalId = 1;

    protected int localId;
    protected String username;
    protected String email;
    protected String password;
    protected String phoneNumber;

    public Account() {

    }

    public Account(String username, String email, String password, String phoneNumber) {
        this.username = username;
        this.email = email;
        this.password = password;
        this.phoneNumber = phoneNumber;
        this.localId = Account.globalId;
        globalId++;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return (true);
        }

        if (obj == null || getClass() != obj.getClass()) {
            return (false);
        }

        Account other = (Account) obj;
        return (this.username.equals(other.username) &&
                this.email.equals(other.email));
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.username, this.email);
    }

    @Override
    public String toString() {
        return (String.join("\n", Arrays.asList("ID: " + this.localId, "Username: " + this.username, "Email: " + this.email, "phoneNumber: " + this.phoneNumber)));
    }

    public int getLocalId() {
        return localId;
    }

    public void setLocalId(int localId) {
        this.localId = localId;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }
}
