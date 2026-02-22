package scs.domain;

import java.time.LocalDateTime;

public class Transaction extends Entity {
    private Long userid;
    private String coinsymbol;
    private String type;
    private Double price;
    private LocalDateTime timestamp;


    public Transaction(Long id, Long userid, String coinsymbol, String type, Double price, LocalDateTime timestamp) {
        super(id);
        this.userid = userid;
        this.coinsymbol = coinsymbol;
        this.type = type;
        this.price = price;
        this.timestamp = timestamp;
    }

    public Long getUserid() {
        return userid;
    }

    public void setUserid(Long userid) {
        this.userid = userid;
    }

    public String getCoinsymbol() {
        return coinsymbol;
    }

    public void setCoinsymbol(String coinsymbol) {
        this.coinsymbol = coinsymbol;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }

    public LocalDateTime getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(LocalDateTime timestamp) {
        this.timestamp = timestamp;
    }
}
