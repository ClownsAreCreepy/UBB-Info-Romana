package scs.ui.controllers.race;

import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import scs.domain.event.Event;
import scs.domain.user.Duck;
import scs.service.EventService;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

public class RaceSimulationController {
    @FXML
    private Label raceTitleLabel;

    @FXML
    private VBox trackContainer;

    @FXML
    private Button startBtn;

    @FXML private Label winnerLabel;

    private Event currentEvent;
    private List<Duck> racers;
    private double[] laneDistances;
    private EventService eventService;

    private final List<Thread> activeThreads = new ArrayList<>();
    private final AtomicBoolean raceFinished = new AtomicBoolean(false);

    private static class RaceTask extends Task<Double> {
        private final Duck duck;
        private final double totalDistance;

        public RaceTask(Duck duck, double totalDistance) {
            this.duck = duck;
            this.totalDistance = totalDistance;
        }

        @Override
        protected Double call() throws Exception {
            double currentDist = 0;
            double currentSpeed = duck.getSpeed();
            double resistance = duck.getResistance();

            long startTime = System.currentTimeMillis();

            while (currentDist < totalDistance) {
                if (isCancelled())
                    break;

                Thread.sleep(50);

                // Move
                double move = currentSpeed / 5.0;
                currentDist += move;

                // Fatigue
                double fatigue = (10.0 - Math.min(resistance, 10.0)) / 200.0;
                currentSpeed = Math.max(1.0, currentSpeed - fatigue);

                updateProgress(currentDist, totalDistance);
                updateMessage(String.format("%.1fm / %.0fm", Math.min(currentDist, totalDistance), totalDistance));
            }

            long endTime = System.currentTimeMillis();
            return (endTime - startTime) / 1000.0; // seconds
        }
    }

    public void initRace(Event event, List<Duck> racers, double[] distances, EventService service) {
        this.currentEvent = event;
        this.racers = racers;
        this.laneDistances = distances;
        this.eventService = service;

        raceTitleLabel.setText("RACE: " + event.getName().toUpperCase());
        setupTrackVisuals();
    }

    private void setupTrackVisuals() {
        trackContainer.getChildren().clear();

        for (int i = 0; i < racers.size(); ++i) {
            Duck d = racers.get(i);

            Label nameLbl = new Label(d.getUsername());
            nameLbl.setStyle("-fx-text-fill: white; -fx-font-weight: bold; -fx-min-width: 80;");

            ProgressBar pb = new ProgressBar(0.0);
            pb.setMaxWidth(Double.MAX_VALUE);
            pb.setStyle("-fx-accent: " + getColorForDuck(i) + ";");
            HBox.setHgrow(pb, Priority.ALWAYS);

            pb.setUserData(i);

            Label statsLb = new Label("0m / " + (int)laneDistances[i] + "m");

            HBox lane = new HBox(10, nameLbl, pb, statsLb);
            lane.setAlignment(Pos.CENTER_LEFT);
            lane.setStyle("-fx-padding: 5; -fx-background-color: rgba(0, 0, 0, 0.2); -fx-background-radius: 5;");

            trackContainer.getChildren().add(lane);
        }
    }

    @FXML
    public void onStartRace() {
        startBtn.setDisable(true);
        winnerLabel.setText("RACE STARTED!");

        for (int i = 0; i < racers.size(); ++i) {
            Duck duck = racers.get(i);
            double distance = laneDistances[i];

            HBox laneBox = (HBox) trackContainer.getChildren().get(i);
            ProgressBar bar = (ProgressBar) laneBox.getChildren().get(1);
            Label statLbl = (Label) laneBox.getChildren().get(2);

            RaceTask task = new RaceTask(duck, distance);

            bar.progressProperty().bind(task.progressProperty());

            task.messageProperty().addListener((obs, old, msg) -> {
                Platform.runLater(() -> statLbl.setText(msg));
            });

            task.setOnSucceeded(e -> {
                if (raceFinished.compareAndSet(false, true))
                    declareWinner(duck, task.getValue());
            });

            Thread th = new Thread(task);
            th.setDaemon(true);     // they die if app closes
            activeThreads.add(th);
            th.start();
        }
    }

    private void declareWinner(Duck winner, double time) {
        String timeStr = String.format("%.2f", time);

        Platform.runLater(() -> {
            winnerLabel.setText("WINNER: " + winner.getUsername());

            String msg = "RACE UPDATE: " + winner.getUsername() +
                         " has won the '" + currentEvent.getName() +
                         "' race in " + timeStr + "s!";

            try {
                eventService.notifySubscribers(currentEvent.getId(), msg);
            } catch (Exception e) {
                System.err.println("Failed to send notification: " + e.getMessage());
            }
        });
    }

    public void stopRace() {
        for (Thread t: activeThreads)
            if (t.isAlive())
                t.interrupt();
    }

    private String getColorForDuck(int index) {
        String[] colors = {"#e74c3c", "#3498db", "#2ecc71", "#f1c40f", "#9b59b6", "#e67e22"};
        return colors[index % colors.length];
    }
}
