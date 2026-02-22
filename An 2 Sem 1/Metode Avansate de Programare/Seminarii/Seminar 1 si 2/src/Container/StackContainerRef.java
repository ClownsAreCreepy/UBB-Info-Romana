package Container;

import App.Task;

public class StackContainerRef extends AbstractArrayContainer {
    public StackContainerRef(int initialCapacity) {
        super(initialCapacity);
    }

    @Override
    public void add(Task task) {
        ensureCapacity();
        data[size++] = task;
    }

    @Override
    public Task remove() {
        if (size == 0) return null;
        Task t = data[--size];
        data[size] = null;
        return t;
    }
}
