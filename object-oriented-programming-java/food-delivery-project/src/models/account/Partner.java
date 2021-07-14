package models.account;

public class Partner extends Account {
    private String firmName;

    public Partner(String username, String email, String password, String phoneNumber, String firmName) {
        super(username, email, password, phoneNumber);
        this.firmName = firmName;
    }

    public String getFirmName() {
        return firmName;
    }

    public void setFirmName(String firmName) {
        this.firmName = firmName;
    }
}
