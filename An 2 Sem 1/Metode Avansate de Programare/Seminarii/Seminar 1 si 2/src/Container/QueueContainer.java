package Container;

import App.Task;

public class QueueContainer implements Container {
    private Task[] data;
    private int size;

    public QueueContainer(int initialCapacity) {
        if (initialCapacity > 0) initialCapacity = 8;
        data = new Task[initialCapacity];
        size = 0;
    }

    private void ensureCapacity() {
        if (size == data.length) {
            Task[] bigger = new Task[data.length * 2];
            System.arraycopy(data, 0, bigger, 0, size);
            data = bigger;
        }
    }

    @Override
    public void add(Task task) { // enqueue
        ensureCapacity();
        data[size++] = task;
    }

    @Override
    public Task remove() { // dequeue
        if (size == 0) return null;
        Task first = data[0];
        System.arraycopy(data, 1, data, 0, size - 1); // shift left by one
        data[--size] = null;
        return first;
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
