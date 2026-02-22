package Sorting;

import App.Task;

import java.util.Arrays;

public class SortingTask extends Task {
    private int[] numbers;
    private AbstractSorter sorter;

    public SortingTask(int id, String descriere, int[] numbers, AbstractSorter sorter) {
        super(id, descriere);
        // clone so the caller's array doesn't get mutated unexpectedly
        this.numbers = numbers.clone();
        this.sorter = sorter;
    }


    public int[] getNumbers() {
        return numbers;
    }

    public void setNumbers(int[] numbers) {
        this.numbers = numbers;
    }

    public AbstractSorter getSorter() {
        return sorter;
    }

    public void setSorter(AbstractSorter sorter) {
        this.sorter = sorter;
    }

    @Override
    public void execute() {
        sorter.sort(numbers);
        System.out.println("sorted (" + sorter.getClass().getSimpleName() + "): " + Arrays.toString(numbers));
    }

    @Override
    public String toString() {
        return "SortingTask{ id='" + getID() + "', descriere='" + getDescriere() + "'}";
    }
}
