package Sorting;

public class BubbleSort extends AbstractSorter {
    @Override
    public void sort(int[] a) {
        boolean swapped;
        int n = a.length;
        do {
            swapped = false;
            for (int i = 1; i < n; i++)
                if (a[i - 1] > a[i]) {
                    int tmp = a[i];
                    a[i] = a[i - 1];
                    a[i - 1] = tmp;
                    swapped = true;
                }
            n--;
        } while (swapped);
    }
}
