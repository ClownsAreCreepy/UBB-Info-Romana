import Domain.ProblemData;
import UI.UI;
import Service.CrazyDuck;

public class Main {
    public static void main(String[] args) throws Exception {
        UI ui = new UI();
        ProblemData data = ui.read();

        CrazyDuck task = new CrazyDuck(data);
        task.setTaskID("duck_taskrunner");
        task.setDescriere("Find minimal race time and assignment");
        task.execute();

        ui.print(data);
    }
}