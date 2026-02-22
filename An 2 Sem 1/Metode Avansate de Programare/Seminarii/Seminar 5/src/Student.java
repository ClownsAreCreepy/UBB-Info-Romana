public class Student extends Entity<Integer> {
    private String name;
    private int group;

    public Student(Integer id, String name, int group) {
        super(id);
        this.name = name;
        this.group = group;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getGroup() {
        return group;
    }

    public void setGroup(int group) {
        this.group = group;
    }
}
