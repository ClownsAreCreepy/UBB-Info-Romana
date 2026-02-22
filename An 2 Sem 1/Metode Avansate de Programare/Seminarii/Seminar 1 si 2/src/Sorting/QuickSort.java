package Sorting;

public class QuickSort extends AbstractSorter {
    @Override
    public void sort(int[] a) {
        quick(a, 0, a.length - 1);
    }

    private void quick(int[] a, int l, int r) {
        if (l >= r) return;
        int p = partition(a, l, r);
        quick(a, l, p - 1);
        quick(a, p + 1, r);
    }

    private int partition(int[] a, int l, int r) {
        int pivot = a[r];
        int i = l - 1;
        for (int j = l; j < r; j++)
            if (a[j] <= pivot) {
                i++;
                swap(a, i, j);
            }
        swap(a, i + 1, r);
        return i + 1;
    }

    private void swap(int[] a, int i, int j) {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}