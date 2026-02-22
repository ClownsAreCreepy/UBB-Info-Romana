//package scs.ui;
//
//import scs.domain.event.Event;
//import scs.domain.event.RaceEvent;
//import scs.domain.group.Herd;
//import scs.domain.group.Performance;
//import scs.domain.user.Duck;
//import scs.domain.user.User;
//import scs.service.*;
//import scs.utilities.errors.DuplicateException;
//import scs.utilities.paging.Page;
//import scs.utilities.paging.Pageable;
//
//import java.text.DecimalFormat;
//import java.time.LocalDate;
//import java.time.format.DateTimeParseException;
//import java.util.ArrayList;
//import java.util.Comparator;
//import java.util.List;
//import java.util.Scanner;
//import java.util.stream.Collectors;
//
//public class Console {
//    private final UserService users;
//    private final FriendshipService friends;
//    private final CommunityService community;
//    private final HerdService herds;
//    private final EventService events;
//    private final Scanner in = new Scanner(System.in);
//
//    public Console(UserService users, FriendshipService friends, CommunityService community, HerdService herds, EventService events) {
//        this.users = users;
//        this.friends = friends;
//        this.community = community;
//        this.herds = herds;
//        this.events = events;
//    }
//
//    public void populate() {
//        System.out.println("Populating Db (Will skip duplicates)");
//
//        // People
//        try {
//            var p1 = users.createPerson("ClownsAreCreepy", "petrupopescut@gmail.com", "pass", "Popescu", "Petru", LocalDate.of(2004, 11, 18), "student");
//            var p2 = users.createPerson("Bonk", "oana@gmail.com", "a1r2t3i4s5t6", "Chiorean", "Oana", LocalDate.of(2005, 6, 24), "artist");
//            var p3 = users.createPerson("Nicol", "bianca@gmail.com", "<3Motorcycles", "Marc", "Bianca-Nicol", LocalDate.of(2006, 12, 5), "artist");
//            var p4 = users.createPerson("Chris", "tarlea@gmail.com", "iHateMinorities", "Tarlea", "Cristian", LocalDate.of(2005, 12, 26), "politician");
//            var p5 = users.createPerson("Oanch", "vlad@gmail.com", "iLoveMinorities", "Oancea", "Vlad", LocalDate.of(2005, 12, 12), "historian");
//            var p6 = users.createPerson("antony", "anto@gmail.com", "SecretRoom1", "Mihaly", "Antony", LocalDate.of(2005, 5, 20), "suedez");
//            var p7 = users.createPerson("Retr0", "contz@gmail.com", "GothMommies:3", "Contz", "Daniel", LocalDate.of(2005, 7, 11), "culturist");
//            var p8 = users.createPerson("Agressive-Ente", "jule@gmail.com", "iAmVeryHot", "Leistner", "Jule", LocalDate.of(2005, 8, 31), "horse osteo-therapist");
//            var p9 = users.createPerson("geo_mommy", "ambra@gmail.com", "iStudyPhilosophyLol", "Rizzeto", "Ambra", LocalDate.of(2005, 5, 5), "trans person");
//            var p10 = users.createPerson("the_angel", "gelussy@gmail.com", "Man", "Czacko", "Angel", LocalDate.of(2005, 6, 17), "engineer");
//
//            // Ducks
//            var d1 = users.createSwimmingDuck("quacker", "q@gmail.com", "1234", 3.2, 8.5);
//            var d2 = users.createFlyingDuck("macker", "m@gmail.com", "5678", 2.5, 6.1);
//            var d3 = users.createHybridDuck("quack quack", "qq@gmail.com", "QQ", 2.4, 3.5);
//            var d4 = users.createHybridDuck("mack mack", "mm@gmail.com", "MM", 6.2, 2.5);
//            var d5 = users.createSwimmingDuck("Adam", "Adam@gmail.com", "GoingForHisFirstSwim", 10.0, 4.5);
//            var d6 = users.createSwimmingDuck("Wilson", "w@gmail.com", "NotReallyADuck", 1.2, 9.5);
//            var d7 = users.createFlyingDuck("Duffy", "d@gmail.com", "cquacq", 5.0, 4.3);
//            var d8 = users.createHybridDuck("Scrooge", "s@gmail.com", "$$$", 1.0, 8.8);
//            var d9 = users.createHybridDuck("Dani", "dan@gmail.com", "641314", 5.2, 10.0);
//            var d10 = users.createHybridDuck("Jule", "pink@gmail.com", "meAgain:)", 7.2, 9.9);
//
//
//            friends.syncWithUsers();
//
//            // Friendships
//            friends.addFriendship(p1.getId(), p2.getId());
//            friends.addFriendship(p1.getId(), p4.getId());
//            friends.addFriendship(p2.getId(), p3.getId());
//            friends.addFriendship(p8.getId(), p9.getId());
//            friends.addFriendship(d6.getId(), p6.getId());
//            friends.addFriendship(d1.getId(), d2.getId());
//            friends.addFriendship(d5.getId(), d6.getId());
//            friends.addFriendship(d7.getId(), d8.getId());
//            friends.addFriendship(p10.getId(), p5.getId());
//            friends.addFriendship(p10.getId(), d5.getId());
//            friends.addFriendship(p7.getId(), p1.getId());
//            friends.addFriendship(d4.getId(), d3.getId());
//            friends.addFriendship(d9.getId(), p7.getId());
//            friends.addFriendship(d10.getId(), p8.getId());
//
//            // Herds
//            var c1 = herds.createHerd("The unknowns");
//            var c2 = herds.createHerd("Among us");
//
//            herds.addDuck(c1.getId(), d1);
//            herds.addDuck(c1.getId(), d2);
//            herds.addDuck(c1.getId(), d3);
//            herds.addDuck(c1.getId(), d4);
//
//            herds.addDuck(c2.getId(), d9);
//            herds.addDuck(c2.getId(), d10);
//            herds.addDuck(c2.getId(), d5);
//
//            System.out.println("Populate done.");
//        } catch (DuplicateException e) {
//            System.out.println("Data already exists. Skipping populate");
//        } catch (Exception e) {
//            System.out.println("Populate error: " + e.getMessage());
//        }
//    }
//
//    private void printMenu() {
//        System.out.println("\n==== DuckSocialNetwork ====");
//        System.out.println("1) add user");
//        System.out.println("2) remove user");
//        System.out.println("3) add friendship");
//        System.out.println("4) remove friendship");
//        System.out.println("5) show number of communities");
//        System.out.println("6) show most sociable community");
//        System.out.println("7) create herd");
//        System.out.println("8) list herds");
//        System.out.println("9) add duck to herd");
//        System.out.println("10) remove duck from herd");
//        System.out.println("11) show herd performance");
//        System.out.println("12) run race (from herd)");
//        System.out.println("13) create event");
//        System.out.println("14) list events");
//        System.out.println("15) subscribe user to event");
//        System.out.println("16) unsubscribe user from event");
//        System.out.println("17) show event details");
//        System.out.println("18) list users (PAGINATE DEMO)");
//        System.out.println("0) exit");
//    }
//
//
//    // --- helpers ---
//    private String readLine(String prompt) {
//        System.out.print(prompt);
//        return in.nextLine().trim();
//    }
//
//    private String readNonBlank(String prompt) {
//        while (true) {
//            String s = readLine(prompt);
//            if (!s.isBlank())
//                return s;
//            System.out.println("can't be empty");
//        }
//    }
//
//    private long readLong(String prompt) {
//        while (true) {
//            String s = readLine(prompt);
//            try {
//                return Long.parseLong(s);
//            } catch (NumberFormatException e) {
//                System.out.println("invalid number");
//            }
//        }
//    }
//
//    private double readDouble(String prompt) {
//        while (true) {
//            String s = readLine(prompt);
//            try {
//                return Double.parseDouble(s);
//            } catch (NumberFormatException e) {
//                System.out.println("invalid number");
//            }
//        }
//    }
//
//    private LocalDate readDate(String prompt) {
//        while (true) {
//            String s = readLine(prompt);
//            try {
//                return LocalDate.parse(s);
//            } catch (DateTimeParseException e) {
//                System.out.println("invalid format. ex: 2000-01-01");
//            }
//        }
//    }
//
//
//    private Duck requireDuck(long id) {
//        var u = users.findById(id);
//        if (!(u instanceof Duck d))
//            throw new RuntimeException("user " + id + " is not a duck");
//        return d;
//    }
//
//
//    // --- actions ---
//    private void addUser() {
//        System.out.println("1=Person, 2=Duck");
//        String t = readLine("> ");
//        switch (t) {
//            case "1" -> addPerson();
//            case "2" -> addDuck();
//            default -> System.out.println("invalid type.");
//        }
//
//        // keep graph in sync with scs.repo
//        friends.syncWithUsers();
//    }
//
//    private void addPerson() {
//        String username = readNonBlank("Username: ");
//        String email = readNonBlank("Email: ");
//        String password = readNonBlank("Password: ");
//        String name = readNonBlank("name: ");
//        String firstName = readNonBlank("firstName: ");
//        LocalDate bd = readDate("Birth date (YYYY-MM-DD): ");
//        String occupation = readNonBlank("Occupation: ");
//
//        var p = users.createPerson(username, email, password, name, firstName, bd, occupation);
//        System.out.println("Created person with id=" + p.getId());
//    }
//
//    private void addDuck() {
//        String username = readNonBlank("Username: ");
//        String email = readNonBlank("Email: ");
//        String password = readNonBlank("Password: ");
//        System.out.println("1=SWIMMING, 2=FLYING, 3=HYBRID");
//        String t = readLine("> ");
//
//
//        double speed = readDouble("Speed:");
//        double rez = readDouble("Resistance: ");
//
//        Duck d = switch (t) {
//            case "1" -> users.createSwimmingDuck(username, email, password, speed, rez);
//            case "2" -> users.createFlyingDuck(username, email, password, speed, rez);
//            case "3" -> users.createHybridDuck(username, email, password, speed, rez);
//            default -> null;
//        };
//
//        if (d != null)
//            System.out.println("Created duck with id=" + d.getId());
//        else
//            System.out.println("invalid type.");
//    }
//
//    private void removeUser() {
//        long id = readLong("id user: ");
//        users.deleteUser(id);
//        // also reflect in graph
//        // (graph removes edges, but we only exposed sync here)
//        friends.syncWithUsers();
//        System.out.println("user deleted.");
//    }
//
//    private void addFriendship() {
//        long a = readLong("id of first user: ");
//        long b = readLong("id of second user: ");
//
//        friends.addFriendship(a, b);
//        System.out.println("Friendship added. :)");
//    }
//
//    private void removeFriendship() {
//        long a = readLong("id of first user: ");
//        long b = readLong("id of second user: ");
//
//        friends.removeFriendship(a, b);
//        System.out.println("Friendship removed. :(");
//    }
//
//    private void showCommunitiesCount() {
//        int k = community.countCommunities();
//        System.out.println("Count: " + k);
//    }
//
//    private void showMostSociable() {
//        CommunityService.CommunitySummary summary = community.mostSociableCommunity();
//        System.out.println("Diameter: " + summary.diameter());
//        summary.members().forEach(u -> System.out.println("- " + u.getUsername()));
//    }
//
//    private void createHerd() {
//        String name = readNonBlank("Herd Name: ");
//        Herd<Duck> c = herds.createHerd(name);
//        System.out.println("Created herd with id=" + c.getId());
//    }
//
//    private void listHerds() {
//        var all = herds.getAll();
//        if (all.isEmpty()) {
//            System.out.println("no herds yet");
//            return;
//        }
//
//        all.forEach(System.out::println);
//    }
//
//    private void addDuckToHerd() {
//        long herdId = readLong("Herd id: ");
//        long duckId = readLong("Duck id: ");
//        var duck = requireDuck(duckId);
//        herds.addDuck(herdId, duck);
//        System.out.println("added. (if it wasn't already)");
//    }
//
//    private void removeFromHerd() {
//        long herdId = readLong("Herd id: ");
//        long duckId = readLong("Duck id: ");
//        herds.deleteDuck(herdId, duckId);
//        System.out.println("removed. (if existed)");
//    }
//
//    private void showHerdPerformance() {
//        long herdId = readLong("Herd id: ");
//        Performance p = herds.performance(herdId);
//        System.out.println("Avg speed: " + p.avgSpeed() + " | Avg resistance = " + p.avgResistance());
//    }
//
//    private void runRaceFromHerd() {
//        long herdId = readLong("Herd id: ");
//        Herd<Duck> herd = herds.findById(herdId);
//
//        int M = (int) readLong("Lanes (M): ");
//        double[] lanes = new double[M];
//        for (int i = 0; i < M; ++i)
//            lanes[i] = readDouble("Distance lane " + (i + 1) + ": ");
//
//        List<Long> candidateIds = herd.getMembers().stream().map(Duck::getId).toList();
//
//        RaceEvent.Result result = events.runRaceInMemory("Race for " + herd.getName(), candidateIds, lanes);
//
//        DecimalFormat df = new DecimalFormat("0.000");
//        result.lanes().forEach(l -> System.out.println("Duck " + l.duckId() + " | Lane " + l.lane() + " | Time: " + df.format(l.time()) + "s"));
//
//        result.lanes().stream()
//                .min(Comparator.comparingDouble(RaceEvent.LaneResult::time))
//                .ifPresent(w -> {
//                    var winnerDuck = users.findById(w.duckId());
//                    System.out.println("\nWINNER IS: " + winnerDuck.getUsername() + "!");
//                });
//    }
//
//    private void createEvent() {
//        String name = readNonBlank("Event name: ");
//        var e = events.createEvent(name);
//        System.out.println("Created event with id=" + e.getId());
//    }
//
//    private void listEvents() {
//        List<Event> list = events.getAll();
//        if (list.isEmpty()) {
//            System.out.println("no events yet");
//            return;
//        }
//        list.forEach(e ->
//                System.out.println("id=" + e.getId() +
//                        " | name=" + e.getName() +
//                        " | subs=" + e.getSubscribers().size()
//                ));
//    }
//
//    private void subscribeUser() {
//        long eventId = readLong("Event id: ");
//        long userId = readLong("User id: ");
//        events.subscribe(eventId, userId);
//        System.out.println("user subscribed.");
//    }
//
//    private void unsubscribeUser() {
//        long eventId = readLong("Event id: ");
//        long userId = readLong("User id: ");
//        events.unsubscribe(eventId, userId);
//        System.out.println("user unsubscribed.");
//    }
//
//    private void showEventDetails() {
//        long eventId = readLong("Event id: ");
//
//        var e = events.findById(eventId);
//
//        System.out.println("Event: " + e.getName());
//        System.out.println("Subscribers:");
//
//        if (e.getSubscribers().isEmpty()) {
//            System.out.println("  none");
//        } else {
//            e.getSubscribers().forEach(uid ->
//                    System.out.println(" - user " + uid)
//            );
//        }
//    }
//
//    private void listUsersPaginated() {
//        int pageSize = (int) readLong("Page size:");
//        int pageNumber = 0;
//
//        while (true) {
//            Pageable request = new Pageable(pageNumber, pageSize);
//            Page<User> page = users.findAll(request);
//
//            System.out.println("\n--- Page " + (pageNumber + 1) + " ---");
//            System.out.println("Total Users in DB: " + page.getTotalElementCount());
//
//            if (page.getElementsOnPage().isEmpty())
//                System.out.println("No users on this page");
//            else
//                page.stream().forEach(u -> System.out.println(" - " + u.getUsername() + "(ID: " + u.getId() + ")"));
//
//            System.out.println("----------");
//            System.out.println("n = next page | p = prev page | x = exit paging");
//            String cmd = readLine("> ");
//
//            if (cmd.equalsIgnoreCase("n")) {
//                if ((pageNumber + 1) * pageSize < page.getTotalElementCount())
//                    pageNumber++;
//                else
//                    System.out.println("Already on last page!");
//            } else if (cmd.equalsIgnoreCase("p")) {
//                if (pageNumber > 0)
//                    pageNumber--;
//                else
//                    System.out.println("Already on the first page!");
//            } else if (cmd.equalsIgnoreCase("X"))
//                break;
//        }
//    }
//
//    public void run() {
//
//        while (true) {
//            printMenu();
//            String opt = readLine(">>> ");
//            try {
//                switch (opt) {
//                    case "1" -> addUser();
//                    case "2" -> removeUser();
//                    case "3" -> addFriendship();
//                    case "4" -> removeFriendship();
//                    case "5" -> showCommunitiesCount();
//                    case "6" -> showMostSociable();
//                    case "7" -> createHerd();
//                    case "8" -> listHerds();
//                    case "9" -> addDuckToHerd();
//                    case "10" -> removeFromHerd();
//                    case "11" -> showHerdPerformance();
//                    case "12" -> runRaceFromHerd();
//                    case "13" -> createEvent();
//                    case "14" -> listEvents();
//                    case "15" -> subscribeUser();
//                    case "16" -> unsubscribeUser();
//                    case "17" -> showEventDetails();
//                    case "18" -> listUsersPaginated();
//                    case "0" -> {
//                        System.out.println("Sper ca e bine :3");
//                        return;
//                    }
//                    default -> System.out.println("invalid option.");
//                }
//            } catch (Exception ex) {
//                System.out.println("Error: " + ex.getMessage());
//            }
//            System.out.println();
//        }
//    }
//}
