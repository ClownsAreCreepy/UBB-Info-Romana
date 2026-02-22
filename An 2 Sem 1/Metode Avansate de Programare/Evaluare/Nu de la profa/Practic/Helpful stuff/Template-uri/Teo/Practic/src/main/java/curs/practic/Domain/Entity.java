package curs.practic.Domain;

public class Entity<ID> {
    private ID id;

    Entity(ID id) {
        this.id = id;
    }

    public ID getId() {
        return id;
    }
    public void setId(ID id) {
        this.id = id;
    }
}

