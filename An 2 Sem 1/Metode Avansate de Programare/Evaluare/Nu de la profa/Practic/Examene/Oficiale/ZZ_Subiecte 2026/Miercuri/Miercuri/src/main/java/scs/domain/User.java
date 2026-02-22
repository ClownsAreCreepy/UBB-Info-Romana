package scs.domain;

public class User extends Entity {
    private String name;
    private Double budget;

    public User(Long id, String name, Double budget) {
        super(id);
        this.name = name;
        this.budget = budget;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Double getBudget() {
        return budget;
    }

    public void setBudget(Double budget) {
        this.budget = budget;
    }

    @Override
    public String toString() {
        return name;
    }
}
