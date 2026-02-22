package TaskRunner;

public class DelayTaskRunner extends AbstractTaskRunner{

    private final long millis;

    public DelayTaskRunner(TaskRunner inner, long millis) {
        super(inner);
        this.millis = millis;
    }

    @Override
    public void executeOneTask(){
        try {
            Thread.sleep(millis);
        } catch (InterruptedException e) {
            e.printStackTrace();
            Thread.currentThread().interrupt(); // be polite
        }
        inner.executeOneTask();
    }
}
