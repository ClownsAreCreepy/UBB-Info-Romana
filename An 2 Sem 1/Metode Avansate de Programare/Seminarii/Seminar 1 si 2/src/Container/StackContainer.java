package Container;

import App.Task;

public class StackContainer implements Container {
    private Task[] data;
    private int size;

    public StackContainer(int initialCapacity) {
        if (initialCapacity <= 0) initialCapacity = 8;
        data = new Task[initialCapacity];
        size = 0;
    }

    // facem capacity pt alocare dinamica
    private void ensureCapacity() {
        if (size == data.length) {
            Task[] bigger = new Task[data.length * 2];
            System.arraycopy(data, 0, bigger, 0, data.length);
            data = bigger;
        }
    }

    @Override
    public void add(Task task) { // push
        ensureCapacity();
        data[size++] = task;
    }

    @Override
    public Task remove() { // pop
        if (size == 0) return null;
        Task t = data[--size];
        data[size] = null;
        return t;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

}
