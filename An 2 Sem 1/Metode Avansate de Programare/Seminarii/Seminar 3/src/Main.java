import Student.*;
import Map.*;
import Repo.*;

import java.util.*;

public class Main {

    // predefined list of students
    public static List<Student> getList() {
        List<Student> list = new ArrayList<>();
        list.add(new Student("1", 9.7f));
        list.add(new Student("2", 7.3f));
        list.add(new Student("3", 6f));
        list.add(new Student("4", 6.9f));
        list.add(new Student("5", 9.5f));
        list.add(new Student("6", 9.9f));
        return list;
    }

    public static void main(String[] args) {

        // I
        // 1. Instantiating students
        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Dan", 4.5f);

        // 2. Creating a hash set of students si adaugam
        HashSet<Student> set = new HashSet<>();
        set.add(s1);
        set.add(s2);
        set.add(s3);

        System.out.println(set.toString());

        // 4. Creating a tree set and a comparator
        Comparator<Student> compareByName = (a, b) -> a.getNume().compareTo(b.getNume());

        TreeSet<Student> treeSet = new TreeSet<>(compareByName);
        treeSet.add(s1);
        treeSet.add(s2);
        treeSet.add(s3);

        System.out.println(treeSet.toString());

        // 5. HashMap and TreeMap
        HashMap<String, Float> hashMap = new HashMap<>();
        hashMap.put("Dan", 4.5f);
        hashMap.put("Ana", 8.5f);
        hashMap.put("Dan", 4.5f);

        System.out.println("HashMap: " + hashMap);

        TreeMap<String, Float>  treeMap = new TreeMap<>();
        treeMap.put("Dan", 4.5f);
        treeMap.put("Ana", 8.5f);
        treeMap.put("Dan", 4.5f);

        System.out.println("TreeMap: " + treeMap);

        // II
        MyMap myMap = new MyMap();

        // add all students
        for (Student s: getList()) {
            myMap.add(s);
        }

        // iterate entries + sort each list alphabetically by student name
        for (Map.Entry<Integer, List<Student>> entry : myMap.getEntries()) {
            List<Student> list = entry.getValue();
            list.sort(Comparator.comparing(st -> st.getNume())); // sort by name
        }

        // display nicely
        for (Map.Entry<Integer, List<Student>> entry : myMap.getEntries()) {
            System.out.println("Media " + entry.getKey() + ": " + entry.getValue());
        }

        // III
        Repository0<Integer, Student_III> repo = new InMemoryRepository<>(new StudentValidator());

        Student_III t1 = new Student_III(1, "Dan", 4.5f);
        Student_III t2 = new Student_III(2, "Ana", 8.5f);
        Student_III t3 = new Student_III(3, "Dan", 4.5f);

        // save
        System.out.println("save t1 -> " + repo.save(t1));
        System.out.println("save t2 -> " + repo.save(t2));
        System.out.println("save t3 -> " + repo.save(t3));

        // try duplicate id
        System.out.println("save duplicate id=1 -> " + repo.save(new Student_III(1, "X", 9f)));
        // ^ returns the entity (spec behavior) and does NOT overwrite

        // read all
        System.out.println("all: ");
        for (Student_III s : repo.findAll())
            System.out.println("  " + s);

        // update existing
        System.out.println("update id=2 -> " + repo.update(new Student_III(2, "Ana", 9.0f)));

        // delete one
        System.out.println("delete id=3 -> " + repo.delete(3));

        // final state
        System.out.println("final: ");
        for (Student_III s : repo.findAll())
            System.out.println("  " + s);
    }
}