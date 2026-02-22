package Container;

import App.Task;

public abstract class AbstractArrayContainer implements Container {
    protected Task[] data;
    protected int size;

    protected AbstractArrayContainer(int initialCapacity) {
        if (initialCapacity > 0) initialCapacity = 8;
        data = new Task[initialCapacity];
        size = 0;
    }

    protected void ensureCapacity() {
        if (size == data.length) {
            Task[] bigger = new Task[data.length * 2];
            System.arraycopy(data, 0, bigger, 0, size);
            data = bigger;
        }
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return (size == 0);
    }


}
