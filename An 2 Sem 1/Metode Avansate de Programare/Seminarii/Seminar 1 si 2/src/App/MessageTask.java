package App;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task {
    private String mesaj;
    private String from;
    private String to;
    private LocalDateTime date;

    // constructor
    public MessageTask(int id, String descriere, String mesaj, String from, String to, LocalDateTime date) {
        super(id, descriere); // chemam constructorul parinte
        this.mesaj = mesaj;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    // getters and setters

    public String getMesaj() {
        return mesaj;
    }

    public void setMesaj(String mesaj) {
        this.mesaj = mesaj;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    // override execute
    @Override
    public void execute() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm:ss");
        System.out.println("[" + date.format(formatter) + "] Message: " + mesaj);
    }

    //toString
    @Override
    public String toString() {
        return "App.MessageTask{" +
                "id='" + getID() + '\'' +
                ", descriere='" + getDescriere() + '\'' +
                ". mesaj='" + mesaj + '\'' +
                ", from='" + from + '\'' +
                ", to='" + to + '\'' +
                ", date=" + date +
                '}';
    }
}
