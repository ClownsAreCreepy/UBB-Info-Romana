package Map;

import Student.Student;

import java.util.*;

public class MyMap {
    // internal static comparator: descending order for Integer keys
    public static class DescIntComparator implements Comparator<Integer> {
        @Override
        public int compare(Integer a, Integer b) {
            return b.compareTo(a);  // desc
        }
    }

    private final TreeMap<Integer, List<Student>> map = new TreeMap<>(new DescIntComparator());

    public void add(Student s) {
        int key = Math.round(s.getMedia());
        // clamp just in case
        if (key < 0) key = 0;
        if (key > 10) key = 10;

        map.computeIfAbsent(key, k -> new ArrayList<>()).add(s);
    }

    // return all entries (key + list)
    public Set<Map.Entry<Integer, List<Student>>> getEntries() {
        return map.entrySet();
    }

    @Override
    public String toString() {
        return map.toString();
    }
}
