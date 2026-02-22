package ui;

import domain.event.RaceEvent;
import domain.group.Card;
import domain.user.Duck;
import service.*;

import java.text.DecimalFormat;
import java.time.LocalDate;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;

public class Console {
    private final UserService users;
    private final FriendshipService friends;
    private final CommunityService community;
    private final CardService cards;
    private final EventService events;
    private final Scanner in = new Scanner(System.in);

    public Console(UserService users, FriendshipService friends, CommunityService community, CardService cards, EventService events) {
        this.users = users;
        this.friends = friends;
        this.community = community;
        this.cards = cards;
        this.events = events;
    }

    public void populate() {
        // People
        var p1 = users.createPerson("ClownsAreCreepy", "petrupopescut@gmail.com", "pass", "Popescu", "Petru", LocalDate.of(2004, 11, 18), "student");
        var p2 = users.createPerson("Bonk", "oana@gmail.com", "a1r2t3i4s5t6", "Chiorean", "Oana", LocalDate.of(2005, 6, 24), "artist");
        var p3 = users.createPerson("Nicol", "bianca@gmail.com", "<3Motorcycles", "Marc", "Bianca-Nicol", LocalDate.of(2006, 12, 5), "artist");
        var p4 = users.createPerson("Chris", "tarlea@gmail.com", "iHateMinorities", "Tarlea", "Cristian", LocalDate.of(2005, 12, 26), "politician");
        var p5 = users.createPerson("Oanch", "vlad@gmail.com", "iLoveMinorities", "Oancea", "Vlad", LocalDate.of(2005, 12, 12), "historian");
        var p6 = users.createPerson("antony", "anto@gmail.com", "SecretRoom1", "Mihaly", "Antony", LocalDate.of(2005, 5, 20), "suedez");
        var p7 = users.createPerson("Retr0", "contz@gmail.com", "GothMommies:3", "Contz", "Daniel", LocalDate.of(2005, 7, 11), "culturist");
        var p8 = users.createPerson("Agressive-Ente", "jule@gmail.com", "iAmVeryHot", "Leistner", "Jule", LocalDate.of(2005, 8, 31), "horse osteo-therapist");
        var p9 = users.createPerson("geo_mommy", "ambra@gmail.com", "iStudyPhilosophyLol", "Rizzeto", "Ambra", LocalDate.of(2005, 5, 5), "trans person");
        var p10 = users.createPerson("the_angel", "gelussy@gmail.com", "Man", "Czacko", "Angel", LocalDate.of(2005, 6, 17), "engineer");

        // Ducks
        var d1 = users.createSwimmingDuck("quacker", "q@gmail.com", "1234", 3.2, 8.5);
        var d2 = users.createFlyingDuck("macker", "m@gmail.com", "5678", 2.5, 6.1);
        var d3 = users.createHybridDuck("quack quack", "qq@gmail.com", "QQ", 2.4, 3.5);
        var d4 = users.createHybridDuck("mack mack", "mm@gmail.com", "MM", 6.2, 2.5);
        var d5 = users.createSwimmingDuck("Adam", "Adam@gmail.com", "GoingForHisFirstSwim", 10.0, 4.5);
        var d6 = users.createSwimmingDuck("Wilson", "w@gmail.com", "NotReallyADuck", 1.2, 9.5);
        var d7 = users.createFlyingDuck("Duffy", "d@gmail.com", "cquacq", 5.0, 4.3);
        var d8 = users.createHybridDuck("Scrooge", "s@gmail.com", "$$$", 1.0, 8.8);
        var d9 = users.createHybridDuck("Dani", "dan@gmail.com", "641314", 5.2, 10.0);
        var d10 = users.createHybridDuck("Jule", "pink@gmail.com", "meAgain:)", 7.2, 9.9);


        friends.syncWithUsers();

        // Friendships
        friends.addFriendship(p1.getId(), p2.getId());
        friends.addFriendship(p1.getId(), p4.getId());
        friends.addFriendship(p2.getId(), p3.getId());
        friends.addFriendship(p8.getId(), p9.getId());
        friends.addFriendship(d6.getId(), p6.getId());
        friends.addFriendship(d1.getId(), d2.getId());
        friends.addFriendship(d5.getId(), d6.getId());
        friends.addFriendship(d7.getId(), d8.getId());
        friends.addFriendship(p10.getId(), p5.getId());
        friends.addFriendship(p10.getId(), d5.getId());
        friends.addFriendship(p7.getId(), p1.getId());
        friends.addFriendship(d4.getId(), d3.getId());
        friends.addFriendship(d9.getId(), p7.getId());
        friends.addFriendship(d10.getId(), p8.getId());

        // Herds
        var c1 = cards.createCard("The unknowns");
        var c2 = cards.createCard("Among us");

        cards.addDuck(c1.getId(), d1);
        cards.addDuck(c1.getId(), d2);
        cards.addDuck(c1.getId(), d3);
        cards.addDuck(c1.getId(), d4);

        cards.addDuck(c2.getId(), d9);
        cards.addDuck(c2.getId(), d10);
        cards.addDuck(c2.getId(), d5);

    }

    private void printMenu() {
        System.out.println("==== DuckSocialNetwork ====");
        System.out.println("1) add user");
        System.out.println("2) remove user");
        System.out.println("3) add friendship");
        System.out.println("4) remove friendship");
        System.out.println("5) show number of communities");
        System.out.println("6) show most sociable community");
        System.out.println("7) create herd");
        System.out.println("8) list herds");
        System.out.println("9) add duck to herd");
        System.out.println("10) remove duck from herd");
        System.out.println("11) show herd performance");
        System.out.println("12) run race (from herd)");
        System.out.println("13) create event");
        System.out.println("14) list events");
        System.out.println("15) subscribe user to event");
        System.out.println("16) unsubscribe user from event");
//        System.out.println("17) notify event subscribers");
//        System.out.println("18) show event details");
        System.out.println("0) exit");
    }


    // --- helpers ---
    private String readLine(String prompt) {
        System.out.print(prompt);
        return in.nextLine().trim();
    }

    private String readNonBlank(String prompt) {
        while (true) {
            String s = readLine(prompt);
            if (!s.isBlank())
                return s;
            System.out.println("can't be empty");
        }
    }

    private long readLong(String prompt) {
        while (true) {
            String s = readLine(prompt);
            try {
                return Long.parseLong(s);
            } catch (NumberFormatException e) {
                System.out.println("invalid number");
            }
        }
    }

    private double readDouble(String prompt) {
        while (true) {
            String s = readLine(prompt);
            try {
                return Double.parseDouble(s);
            } catch (NumberFormatException e) {
                System.out.println("invalid number");
            }
        }
    }

    private LocalDate readDate(String prompt) {
        while (true) {
            String s = readLine(prompt);
            try {
                return LocalDate.parse(s);
            } catch (DateTimeParseException e) {
                System.out.println("invalid format. ex: 2000-01-01");
            }
        }
    }


    private Duck requireDuck(long id) {
        var u = users.findById(id);
        if (!(u instanceof Duck d))
            throw new RuntimeException("user " + id + " is not a duck");
        return d;
    }


    // --- actions ---
    private void addUser() {
        System.out.println("Add user:");
        System.out.println("  type? 1 = Person, 2 = Duck");
        String t = readLine("> ");
        switch (t) {
            case "1" -> addPerson();
            case "2" -> addDuck();
            default -> System.out.println("tip invalid.");
        }

        // keep graph in sync with repo
        friends.syncWithUsers();
    }

    private void addPerson() {
        String username = readNonBlank("Username: ");
        String email = readNonBlank("Email: ");
        String password = readNonBlank("Password: ");
        String nume = readNonBlank("Nume: ");
        String prenume = readNonBlank("Prenume: ");
        LocalDate dn = readDate("Data nasterii (YYYY-MM-DD): ");
        String ocup = readNonBlank("Ocupatie: ");

        var p = users.createPerson(username, email, password, nume, prenume, dn, ocup);
        System.out.println("Created person with id=" + p.getId());
    }

    private void addDuck() {
        String username = readNonBlank("Username: ");
        String email = readNonBlank("Email: ");
        String password = readNonBlank("Password: ");
        System.out.println("Duck type? 1 = SWIMMING, 2 = FLYING, 3 = HYBRID");
        String t = readLine("> ");


        double speed = readDouble("Viteza (nr real):");
        double rez = readDouble("Rezistenta (nr real): ");

        Duck d;

        switch (t) {
            case "1" -> d = users.createSwimmingDuck(username, email, password, speed, rez);
            case "2" -> d = users.createFlyingDuck(username, email, password, speed, rez);
            case "3" -> d = users.createHybridDuck(username, email, password, speed, rez);
            default -> {
                System.out.println("tip invalid.");
                return;
            }
        }
        System.out.println("Created duck with id=" + d.getId());
    }

    private void removeUser() {
        long id = readLong("id user: ");
        users.deleteUser(id);
        // also reflect in graph
        // (graph removes edges, but we only exposed sync here)
        friends.syncWithUsers();
        System.out.println("user deleted.");
    }

    private void addFriendship() {
        long a = readLong("id of first user: ");
        long b = readLong("id of second user: ");

        friends.addFriendship(a, b);
        System.out.println("Prieteni adaugati :)");
    }

    private void removeFriendship() {
        long a = readLong("id of first user: ");
        long b = readLong("id of second user: ");

        friends.removeFriendship(a, b);
        System.out.println("Prietenie stearsa :(");
    }

    private void showCommunitiesCount() {
        int k = community.countCommunities();
        System.out.println("numar comunitati: " + k);
    }

    private void showMostSociable() {
        var summary = community.mostSociableCommunity();
        System.out.println("diametru comunitate: " + summary.getDiameter());
        System.out.println("membri: ");
        summary.getMembers().forEach(u ->
                System.out.println("  - id=" + u.getId() + " @" + u.getUsername() + " (" + u.getClass().getSimpleName() + ")"));
    }

    private void createCard() {
        String name = readNonBlank("Herd Name: ");
        var c = cards.createCard(name);
        System.out.println("Created herd with id=" +  c.getId());
    }

    private void listCards() {
        var all = cards.getAll();
        if (all.isEmpty()) {
            System.out.println("no herds yet");
            return;
        }

        all.stream()
                .sorted(Comparator.comparingLong(Card::getId))
                .forEach(System.out::println);
    }

    private void addDuckToCard() {
        long cardId = readLong("Herd id: ");
        long duckId = readLong("Duck id: ");
        var duck = requireDuck(duckId);
        cards.addDuck(cardId, duck);
        System.out.println("added. (if it wasn't already)");
    }

    private void removeFromCard() {
        long cardId = readLong("Herd id: ");
        long duckId = readLong("Duck id: ");
        cards.deleteDuck(cardId, duckId);
        System.out.println("removed. (if existed)");
    }

    private void showCardPerformance() {
        long cardId = readLong("Herd id: ");
        var p = cards.performance(cardId);
        System.out.println("Average speed = " + p.avgSpeed() + ", average resistance = " + p.avgResistance());
    }

    private void runRaceFromCard() {
        long cardId = readLong("Herd id: ");
        var card = cards.findById(cardId);

        int M = (int) readLong("M (number of lanes): ");
        double[] balize = new double[M];
        System.out.println("Enter " + M + " distances(meters) for lanes 1.." + M + ":");
        for (int i = 0; i < M; i++)
            balize[i] = readDouble("d" + (i + 1) + ": ");

        var candidates = new ArrayList<>(card.getMembers());
        var race = new RaceEvent(1000L + cardId, "Race@" + card.getNumeCard(), candidates, balize, M);

        var result = race.runRace();

        var df = new DecimalFormat("0.000");

        result.lanes().forEach(l ->
                System.out.println("Duck " + l.duckId() + " on lane " + l.lane() + ": t = " + df.format(l.time()) + "s (d=" + l.distance() + "m, v=" + l.velocity() + "m/s)")
        );
        System.out.println("Total race time = " + String.format("%.3f", result.totalTime()) + "s");
    }

    private void createEvent() {
        String name = readNonBlank("Event name: ");
        var e = events.createEvent(name);
        //System.out.println("Created event with id=" + e.getId());
    }

    private void listEvents() {
        var list = events.getAll();
        if (list.isEmpty()) {
            System.out.println("no events yet");
            return;
        }
        list.forEach(e ->
                System.out.println("id=" + e.getId() +
                        " | name=" + e.getName() +
                        " | subs=" + e.getSubscribers().size() +
                        " | lastNotified=" + e.getLastNotifiedAt())
        );
    }

    private void subscribeUser() {
        long eventId = readLong("Event id: ");
        long userId = readLong("User id: ");
        events.subscribe(eventId, userId);
        //System.out.println("user subscribed.");
    }

    private void unsubscribeUser() {
        long eventId = readLong("Event id: ");
        long userId = readLong("User id: ");
        events.unsubscribe(eventId, userId);
        //System.out.println("user unsubscribed.");
    }

    private void notifyEvent() {
        long eventId = readLong("Event id: ");
        String msg = readNonBlank("Message: ");

        events.notifySubscribers(eventId, msg);
        System.out.println("notification saved.");
    }

    private void showEventDetails() {
        long eventId = readLong("Event id: ");

        var e = events.findById(eventId);

        System.out.println("Event: " + e.getName());
        System.out.println("Last notified: " + e.getLastNotifiedAt());
        System.out.println("Message: " + e.getLastNotification());
        System.out.println("Subscribers:");

        if (e.getSubscribers().isEmpty()) {
            System.out.println("  none");
        } else {
            e.getSubscribers().forEach(uid ->
                    System.out.println("  - user " + uid)
            );
        }
    }


    public void run() {

        while (true) {
            printMenu();
            String opt = readLine(">>> ");
            try {
                switch (opt) {
                    case "1" -> addUser();
                    case "2" -> removeUser();
                    case "3" -> addFriendship();
                    case "4" -> removeFriendship();
                    case "5" -> showCommunitiesCount();
                    case "6" -> showMostSociable();
                    case "7" -> createCard();
                    case "8" -> listCards();
                    case "9" -> addDuckToCard();
                    case "10" -> removeFromCard();
                    case "11" -> showCardPerformance();
                    case "12" -> runRaceFromCard();
                    case "13" -> createEvent();
                    case "14" -> listEvents();
                    case "15" -> subscribeUser();
                    case "16" -> unsubscribeUser();
//                    case "17" -> notifyEvent();
//                    case "18" -> showEventDetails();
                    case "0" -> {
                        System.out.println("Sper ca e bine :3");
                        return;
                    }
                    default -> System.out.println("invalid option.");
                }
            } catch (RuntimeException ex) {
                System.out.println("eroare: " + ex.getMessage());
            }
            System.out.println();
        }
    }
}
