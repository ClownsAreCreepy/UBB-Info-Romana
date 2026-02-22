package scs.domain;

public class Car extends Entity{
    private String denumire;
    private String descriere;
    private Integer pret;
    private String status;
    private String comment;

    public Car(Long id, String denumire, String descriere, Integer pret, String status, String comment) {
        super(id);
        this.denumire = denumire;
        this.descriere = descriere;
        this.pret = pret;
        this.status = status;
        this.comment = comment;
    }

    public String getDenumire() {
        return denumire;
    }

    public void setDenumire(String denumire) {
        this.denumire = denumire;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    public Integer getPret() {
        return pret;
    }

    public void setPret(Integer pret) {
        this.pret = pret;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getComment() {
        return comment;
    }

    public void setComment(String comment) {
        this.comment = comment;
    }

    @Override
    public String toString() {
        return denumire + " - " + status;
    }
}
