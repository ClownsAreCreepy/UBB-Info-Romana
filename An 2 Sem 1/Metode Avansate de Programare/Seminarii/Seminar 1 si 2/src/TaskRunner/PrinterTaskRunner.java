package TaskRunner;

public class PrinterTaskRunner extends AbstractTaskRunner {
    public PrinterTaskRunner(TaskRunner inner) {
        super(inner);
    }

    @Override
    public void executeOneTask() {
        inner.executeOneTask(); // run the actual task
        System.out.println("[printer] task executed at " + now("yyyy-MM-dd HH:mm:ss"));
    }
}