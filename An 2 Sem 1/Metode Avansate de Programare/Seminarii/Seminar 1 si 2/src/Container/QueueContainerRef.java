package Container;

import App.Task;

public class QueueContainerRef extends AbstractArrayContainer{
    public QueueContainerRef(int initialCapacity){
        super(initialCapacity);
    }

    @Override
    public void add(Task task) { // enqueue
        ensureCapacity();
        data[size++] = task;
    }

    @Override
    public Task remove() {
        if (size == 0) return null;
        Task first = data[0];
        System.arraycopy(data, 1, data, 0, size - 1);
        data[--size] = null;
        return first;
    }
}
