public class Tema extends Entity<String> {
    private final String descriere;

    public Tema(String s, String descriere) {
        super(s);
        this.descriere = descriere;
    }

    public String getDescriere() {
        return descriere;
    }
}
