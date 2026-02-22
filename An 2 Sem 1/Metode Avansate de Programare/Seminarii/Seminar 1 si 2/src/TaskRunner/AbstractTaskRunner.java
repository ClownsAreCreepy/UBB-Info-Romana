package TaskRunner;

import App.Task;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public abstract class AbstractTaskRunner implements TaskRunner {
    protected final TaskRunner inner;

    public AbstractTaskRunner(TaskRunner inner) {
        this.inner = inner;
    }

    // default delegations (kids can override if they need)
    @Override
    public void addTask(Task t) {
        inner.addTask(t);
    }

    @Override
    public boolean hasTask() {
        return inner.hasTask();
    }

    @Override
    public void executeAll() {
        while(hasTask())
            executeOneTask();
    }

    // helper
    protected String now(String pattern) {
        return LocalDateTime.now().format(DateTimeFormatter.ofPattern(pattern));
    }
}
