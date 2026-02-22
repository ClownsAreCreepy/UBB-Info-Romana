package Service;

import Domain.Duck;

import java.util.Arrays;
import java.util.Comparator;

public class TaskSort {
    // sort ducks by stamina descending (helper for greedy)
    public static Duck[] byStaminaDesc(Duck[] ducks) {
        Duck[] copy = ducks.clone();
        Arrays.sort(copy, Comparator.comparingInt(Duck::getResistance).reversed());
        return copy;
    }
}
