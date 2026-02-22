package Factory;

import Container.Container;
import Container.StackContainer;
import Container.QueueContainer;

public class TaskContainerFactory implements Factory { // Singleton Version

    // creem o singura instanta statica
    private static final TaskContainerFactory instance = new TaskContainerFactory();

    // facem constructor privat, astfel nimeni nu foloseste "new"
    private TaskContainerFactory() {}

    // facem o metoda publica sa luam singura instanta
    public static TaskContainerFactory getInstance() {
        return instance;
    }

    @Override
    public Container createContainer(Strategy strategy) {
        switch (strategy) {
            case LIFO:
                return new StackContainer(8);
            case FIFO:
                return new QueueContainer(8);
            default:
                throw new IllegalArgumentException("unknown strategy: " + strategy);
        }
    }
}
