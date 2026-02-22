import java.util.*;
import java.util.stream.Collectors;

public class Sem5App {
    private static List<Student> getStudents() {
        return List.of(
                new Student(1, "Ana", 221),
                new Student(2, "Lana", 221),
                new Student(3, "Dana", 221),
                new Student(4, "Oana", 222),
                new Student(5, "Ioana", 222)
        );
    }

    private static List<Tema> getTeme() {
        return List.of(
                new Tema("1", "ana are mere"),
                new Tema("2", "oana are mere"),
                new Tema("3", "ioana are mere"),
                new Tema("4", "dana are mere"),
                new Tema("5", "lana are mere")
        );
    }

    private static List<Nota> getNote(List<Student> students, List<Tema> teme) {
        List<Nota> all = new ArrayList<>( List.of(
                // TEME
                new Nota(students.get(0), teme.get(0), 10.0, "Prof1"),
                new Nota(students.get(0), teme.get(1), 9.0, "Prof1"),
                new Nota(students.get(2), teme.get(1), 9.6, "Prof1"),
                new Nota(students.get(2), teme.get(0), 7.5, "Prof2"),
                new Nota(students.get(3), teme.get(0), 4.5, "Prof2"),
                new Nota(students.get(4), teme.get(2), 9.5, "Prof2"),
                new Nota(students.get(4), teme.get(3), 7.2, "Prof2"),
                new Nota(students.get(2), teme.get(4), 7.9, "Prof2")
        ));

        all.addAll(List.of(
                // EXAMENE
                new Nota(students.get(0), "Math", 8.5, "ProfX", AssessmentType.EXAM),
                new Nota(students.get(1), "Math", 7.0, "ProfX", AssessmentType.EXAM),
                new Nota(students.get(2), "Physics", 9.0, "ProfX", AssessmentType.EXAM),
                new Nota(students.get(3), "Math", 6.0, "ProfX", AssessmentType.EXAM),
                new Nota(students.get(4), "Physics", 9.5, "ProfX", AssessmentType.EXAM)
        ));

        return all;
    }

    private static List<Examen> getExamene() {
        return List.of(
                new Examen("Ana", "Math", 9.0),
                new Examen("Lana", "Math", 7.0),
                new Examen("Dana", "Math", 8.0),
                new Examen("Ana", "Physics", 8.0),
                new Examen("Oana", "Math", 6.0),
                new Examen("Ioana", "Math", 9.0),
                new Examen("Ioana", "Physics", 9.5),
                new Examen("Oana", "Physics", 7.5)

        );
    }

    private static void report1(List<Nota> note, String s) {
        Map<Student, List<Nota>> studentsGrades = note.stream()
                .collect(Collectors.groupingBy(Nota::getStudent));
        studentsGrades.entrySet().stream()
                .filter(e -> e.getKey().getName().contains(s))
                .sorted((e1, e2) -> {
                    double avg1 = getAverage(e1.getValue());
                    double avg2 = getAverage(e2.getValue());

                    return -Double.compare(avg1, avg2);
                })
                .forEach(e -> System.out.println(e.getKey().getName() + " medie " + getAverage(e.getValue())));

    }

    private static double getAverage(List<Nota> note) {
        double sum = note.stream().map(Nota::getValue).reduce(0.0, Double::sum);

        return sum / note.size();
    }

    private static void report2(List<Nota> note, String name) {
        Map<String, Double> r = note.stream()
                .filter(nota -> nota.getProfesor().contains(name))
                .collect(Collectors.groupingBy(Nota::getProfesor, Collectors.averagingDouble(Nota::getValue)))
                .entrySet().stream()
                .sorted(Collections.reverseOrder(Map.Entry.comparingByValue()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, ((o1, o2) -> o1), LinkedHashMap::new));
        System.out.println(r);
    }

    private static void report3(List<Nota> note, int group) {
        note.stream()
                .filter(nota -> nota.getStudent().getGroup() == group)
                .collect(Collectors.groupingBy(Nota::getStudent, Collectors.counting()))
                .entrySet().stream()
                .sorted(Collections.reverseOrder(Map.Entry.comparingByValue()))
                .forEach(e -> System.out.println(e.getKey().getName() + " numar note " + e.getValue()));
    }

    private static void report4(List<Nota> note, int startingGroup) {
        note.stream()
                .collect(Collectors.groupingBy(n -> n.getStudent().getGroup(), Collectors.averagingDouble(n -> n.getValue())))
                .entrySet().stream()
                .filter(e -> Integer.toString(e.getKey()).startsWith(Integer.toString(startingGroup)))
                .sorted(Map.Entry.<Integer, Double>comparingByValue().reversed())
                .forEach(e -> System.out.println(e.getKey() + " media notelor " + e.getValue()));
    }

    private static void report5(List<Nota> note) {
        note.stream()
                .collect(Collectors.groupingBy(n -> n.getStudent().getGroup()))
                .entrySet().stream()
                .map(e -> {
                    var grupa = e.getKey();
                    var notes =  e.getValue();

                    var averageGrade = notes.stream().mapToDouble(Nota::getValue).average().orElse(0.0);
                    var distinctStudents = notes.stream().map(n -> n.getStudent().getName()).distinct().count();

                    double actualAverage = distinctStudents == 0 ? 0 : averageGrade / distinctStudents;

                    return new AbstractMap.SimpleEntry<>(grupa, actualAverage);
                })
                .sorted(Collections.reverseOrder(Map.Entry.comparingByValue()))
                .forEach(e -> System.out.println(e.getKey() + " raport medie per student " + e.getValue()));
    }

    private static void report6(List<Student> students, List<Examen> examene) {
        // name -> group lookup
        Map<String, Integer> studentToGroup = students.stream()
                .collect(Collectors.toMap(Student::getName, Student::getGroup));

        // group by group, then by subjects, averaging grade
        Map<Integer, Map<String, Double>> res = examene.stream()
                .collect(Collectors.groupingBy(
                        ex -> studentToGroup.getOrDefault(ex.getStudentName(), -1),
                        Collectors.groupingBy(
                                Examen::getSubject,
                                Collectors.averagingDouble(Examen::getGrade)
                        )
                ));

        // print, sorted by group asc then subject asc
        res.entrySet().stream()
                .sorted(Map.Entry.comparingByKey())
                .forEach(e -> {
                    int grupa = e.getKey();
                    System.out.println("Groupa " + grupa + ":");

                    e.getValue().entrySet().stream()
                            .sorted(Map.Entry.comparingByKey())
                            .forEach(sub -> System.out.printf(" %s -> %.2f%n", sub.getKey(), sub.getValue()));
                });
    }

    private static void report7(List<Nota> note) {
        // split by type, then average by student
        var homeworkAvgByStudent = note.stream()
                .filter(n -> n.getType() == AssessmentType.HOMEWORK)
                .collect(Collectors.groupingBy(
                        Nota::getStudent,
                        Collectors.averagingDouble(Nota::getValue)
                ));

        var examAvgByStudent = note.stream()
                .filter(n -> n.getType() == AssessmentType.EXAM)
                .collect(Collectors.groupingBy(
                        Nota::getStudent,
                        Collectors.averagingDouble(Nota::getValue)
                ));

        // union of all students who have either
        var allStudents = new HashSet<Student>();
        allStudents.addAll(homeworkAvgByStudent.keySet());
        allStudents.addAll(examAvgByStudent.keySet());

        allStudents.stream()
                .sorted(Comparator.comparing(Student::getName))
                .forEach(s -> {
                    double hw = homeworkAvgByStudent.getOrDefault(s, 0.0);
                    double ex = examAvgByStudent.getOrDefault(s, 0.0);

                    System.out.printf("%s -> teme: %.2f | examene: %.2f%n", s.getName(), hw, ex);
                });
    }

    public static void main(String[] args) {
        var students = getStudents();
        var notes = getNote(students, getTeme());
        var exams = getExamene();

        //report1(notes, "a");
        //report2(notes, "Prof");
        //report3(notes, 222);
        //report4(notes, 2);
        //report5(notes);
        //report6(students, exams);
        report7(notes);
    }
}