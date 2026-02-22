package scs.ui.controllers.race;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.StringConverter;
import scs.domain.event.Event;
import scs.domain.event.RaceEvent;
import scs.domain.group.Herd;
import scs.domain.user.Duck;
import scs.domain.user.User;
import scs.service.EventService;
import scs.service.HerdService;
import scs.service.social.UserService;
import scs.utilities.errors.ValidationException;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observable;
import scs.utilities.observer.Observer;

import java.util.ArrayList;
import java.util.List;

public class RaceController implements Observer<EntityChangeEvent<?>> {
    @FXML private ComboBox<Event> eventSelector;
    @FXML private ComboBox<Herd<Duck>> herdSelector;
    @FXML private TextField txtLanes;
    @FXML private VBox lanesContainer;  // DYNAMIC CONTAINER
    @FXML private Label statusLabel;

    private final ObservableList<Event> eventsModel = FXCollections.observableArrayList();
    private final ObservableList<Herd<Duck>> herdsModel = FXCollections.observableArrayList();

    private HerdService herdService;
    private EventService eventService;
    private User currentUser;

    private List<TextField> laneInputs = new ArrayList<>();

    public void setServices(HerdService hs, EventService es, User loggedIn) {
        this.herdService = hs;
        this.eventService = es;
        this.currentUser = loggedIn;

        ((Observable) this.herdService).addObserver(this);
        ((Observable) this.eventService).addObserver(this);

        initUi();

        eventsModel.setAll(eventService.getAll());
        herdsModel.setAll(herdService.getAll());
    }

    private void initUi() {
        eventSelector.setItems(eventsModel);
        herdSelector.setItems(herdsModel);

        eventSelector.setConverter(new StringConverter<>() {
            @Override
            public String toString(Event event) {
                return (event == null) ?  "" : event.getName();
            }

            @Override
            public Event fromString(String s) {
                return null;
            }
        });

        herdSelector.setConverter(new StringConverter<>() {
            @Override
            public String toString(Herd<Duck> herd) {
                return (herd == null) ? "" : herd.getName();
            }

            @Override
            public Herd<Duck> fromString(String s) {
                return null;
            }
        });
    }

    @Override
    public void update(EntityChangeEvent<?> event) {
        Platform.runLater(() -> {
            Object data = event.data();

            if (data instanceof Event )
                handleEventUpdate((EntityChangeEvent<Event>) event);
            else if  (data instanceof Herd)
                handleHerdUpdate((EntityChangeEvent<Herd<Duck>>) event);
        });
    }

    private void handleEventUpdate(EntityChangeEvent<Event> event) {
        Event data = event.data();
        switch (event.type()) {
            case ADD:
                eventsModel.add(data);
                break;

            case DELETE:
                eventsModel.removeIf(e -> e.getId().equals(data.getId()));
                if (isSelected(eventSelector, data.getId()))
                    eventSelector.getSelectionModel().clearSelection();
                break;

            case UPDATE:
                int idx = findIndexByEventId(eventsModel, data.getId());
                if (idx != -1) {
                    eventsModel.set(idx, data);
                    if (isSelected(eventSelector, data.getId()))
                        eventSelector.getSelectionModel().select(idx);
                }
                break;
        }
    }

    private void handleHerdUpdate(EntityChangeEvent<Herd<Duck>> event) {
        Herd<Duck> data = event.data();
        switch (event.type()) {
            case ADD:
                herdsModel.add(data);
                break;

            case DELETE:
                herdsModel.removeIf(h -> h.getId().equals(data.getId()));
                if (isSelected(herdSelector, data.getId()))
                    herdSelector.getSelectionModel().clearSelection();
                break;

            case UPDATE:
                int idx = findIndexByIdHerds(herdsModel, data.getId());
                if (idx != -1) {
                    herdsModel.set(idx, data);
                    if (isSelected(herdSelector, data.getId()))
                        herdSelector.getSelectionModel().select(idx);
                }
                break;
        }
    }

    private int findIndexByEventId(ObservableList<Event> list, Long id) {
        for (int i = 0; i < list.size(); ++i)
            if (list.get(i).getId().equals(id))
                return i;
        return -1;
    }

    private int findIndexByIdHerds(ObservableList<Herd<Duck>> list, long id) {
        for (int i = 0; i < list.size(); ++i)
            if (list.get(i).getId().equals(id))
                return i;
        return -1;
    }

    private boolean isSelected(ComboBox<?> box, Long id) {
        Object selected = box.getValue();
        return switch (selected) {
            case Event e -> e.getId().equals(id);
            case Herd<?> h -> h.getId().equals(id);
            case null, default -> false;
        };

    }

    @FXML public void onGenerateTrack() {
        lanesContainer.getChildren().clear();
        laneInputs.clear();
        statusLabel.setText("");

        try {
            int m = Integer.parseInt(txtLanes.getText());
            if (m <= 0 || m > 50)
                throw new ValidationException("lane range", "InvalidRange");

            for (int i = 0; i < m; ++i) {
                HBox raw = new HBox(10);
                Label lbl = new Label("Lane " + (i + 1) + " Distance:");
                TextField tf = new TextField("100.0");

                raw.getChildren().addAll(lbl, tf);
                lanesContainer.getChildren().add(raw);

                laneInputs.add(tf);
            }
        } catch (NumberFormatException e) {
            statusLabel.setText("Please enter a number of lanes (1-50).");
        }
    }

    @FXML
    public void onRunRace() {
        Event selectedEvent = eventSelector.getValue();
        Herd<Duck> selectedHerd = herdSelector.getValue();

        if (selectedHerd == null || selectedEvent == null) {
            statusLabel.setText("Please select both a Spectator Event and a Racing Herd.");
            return;
        }

        if (laneInputs.isEmpty()) {
            statusLabel.setText("Please generate track lanes first.");
            return;
        }

        try {
            // read inputs
            double[] lanes = new double[laneInputs.size()];
            for (int i = 0; i < laneInputs.size(); ++i)
                lanes[i] = Double.parseDouble(laneInputs.get(i).getText());

            // prepare data
            List<Duck> allMembers = herdService.members(selectedHerd.getId());

            // Filter swimmers
            List<Duck> qualifiedRacers = allMembers.stream()
                    .filter(RaceEvent::canSwim)
                    .toList();

            if (qualifiedRacers.size() < lanes.length) {
                statusLabel.setText("Not enough swimming ducks in herd for " + lanes.length + " lanes." +
                                    "(Herd has " + allMembers.size() + ", but only " + qualifiedRacers.size() + " can swim.");
                return;
            }

            List<Duck> actualRacers = qualifiedRacers.subList(0, lanes.length);

            openSimulationWindow(selectedEvent, actualRacers, lanes);

        } catch (ValidationException e) {
            statusLabel.setText("Invalid distance value in lanes.");
        } catch (Exception e) {
            e.printStackTrace();
            statusLabel.setText("Error: " + e.getMessage());
        }
    }

    private void openSimulationWindow(Event event, List<Duck> racers, double[] distances) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/scs/side-views/race/race-simulation-view.fxml"));
            Parent root = loader.load();

            RaceSimulationController ctrl = loader.getController();

            ctrl.initRace(event, racers, distances, eventService);

            Stage stage = new Stage();
            stage.setTitle("LIVE RACE: " + event.getName());
            stage.setScene(new Scene(root));

            stage.setOnCloseRequest(e -> ctrl.stopRace());

            stage.show();
        } catch (Exception e) {
            e.printStackTrace();
            statusLabel.setText("Failed to open simulation: " + e.getMessage());
        }
    }

    public void cleanup() {
        if (herdService != null) ((Observable) herdService).removeObserver(this);
        if (eventService != null) ((Observable) herdService).removeObserver(this);
    }
}
