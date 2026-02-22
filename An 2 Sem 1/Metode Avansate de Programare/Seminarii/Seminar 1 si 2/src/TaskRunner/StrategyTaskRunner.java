package TaskRunner;

import Container.*;
import Factory.*;
import App.*;

public class StrategyTaskRunner implements TaskRunner {
    private final Container container;

    // main ctor (uses the singleton factory)
    public StrategyTaskRunner(Strategy strategy) {
        this(TaskContainerFactory.getInstance(), strategy);
    }

    // flexible ctor (DI)
    public StrategyTaskRunner(Factory factory, Strategy strategy) {
        this.container = factory.createContainer(strategy);
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public void executeOneTask() {
        if (!container.isEmpty()) {
            Task t = container.remove();
            t.execute();
        }
    }

    @Override
    public void executeAll() {
        while (!container.isEmpty()) {
            executeOneTask();
        }
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
