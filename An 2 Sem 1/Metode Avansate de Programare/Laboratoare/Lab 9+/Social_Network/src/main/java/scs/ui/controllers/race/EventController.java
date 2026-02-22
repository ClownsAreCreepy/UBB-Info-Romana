package scs.ui.controllers.race;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.effect.DropShadow;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Modality;
import javafx.stage.Stage;
import scs.domain.event.Event;
import scs.domain.user.User;
import scs.service.EventService;
import scs.service.social.UserService;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observer;

import java.util.List;

public class EventController implements Observer<EntityChangeEvent<Event>> {
    @FXML private FlowPane eventsGrid;
    @FXML private TextField newEventName;

    private Stage activePopupStage;
    private ListView<String> activePopupList;
    private Long activePopupEventId;

    private EventService eventService;
    private UserService userService;
    private User currentUser;

    public void setServices(EventService es, UserService us, User user) {
        this.eventService = es;
        this.userService = us;
        this.currentUser = user;

        this.eventService.addObserver(this);

        refreshGrid();
    }

    @Override
    public void update(EntityChangeEvent<Event> event) {
        Platform.runLater(() -> {
            Event e = event.data();
            switch (event.type()) {
                case ADD:
                    addCardToGrid(e);
                    break;
                case DELETE:
                    removeCardFromGrid(e.getId());
                    break;
                case UPDATE:
                    updateCardInGrid(e);
                    break;
            }
        });
    }

    private void refreshGrid() {
        eventsGrid.getChildren().clear();

        for (Event event : eventService.getAll()) {
            VBox card = createEventCard(event);
            eventsGrid.getChildren().add(card);
        }
    }

    private Node findCardById(Long id) {
        for (Node node : eventsGrid.getChildren())
            if (id.equals(node.getUserData()))
                return node;
        return null;
    }

    private void addCardToGrid(Event event) {
        if (findCardById(event.getId()) != null)
            return;

        VBox card = createEventCard(event);
        eventsGrid.getChildren().add(card);
    }

    private void removeCardFromGrid(Long id) {
        Node target = findCardById(id);
        if (target != null)
            eventsGrid.getChildren().remove(target);

        if (id.equals(activePopupEventId) && activePopupStage != null)
            activePopupStage.close();
    }

    private void updateCardInGrid(Event event) {
        Node target = findCardById(event.getId());
        if (target != null){
            int index = eventsGrid.getChildren().indexOf(target);
            VBox newCard = createEventCard(event);
            eventsGrid.getChildren().set(index, newCard);
        } else
            addCardToGrid(event);

        if (event.getId().equals(activePopupEventId))
            refreshActivePopup(event);
    }

    private VBox createEventCard(Event event) {
        // Card look
        VBox card = new VBox(10);
        card.setPrefSize(200, 150);
        card.setStyle("-fx-background-color: white; -fx-background-radius: 10; -fx-padding: 15;");
        card.setAlignment(Pos.CENTER);

        card.setUserData(event.getId());

        // Shadow Effect
        DropShadow shadow = new DropShadow();
        shadow.setColor(Color.gray(0.2, 0.3));
        shadow.setRadius(10);
        card.setEffect(shadow);

        // Name
        Label nameLbl = new Label(event.getName());
        nameLbl.setFont(Font.font("System Bold", 18));
        nameLbl.setWrapText(true);
        nameLbl.setAlignment(Pos.CENTER);

        // Subscriber count
        int subCount = event.getSubscribers().size();
        Hyperlink subLink = new Hyperlink(subCount + " Subscribers");
        subLink.setStyle("-fx-text-fill: #3498db; -fx-font-size: 12px; -fx-border-color: transparent;");

        subLink.setOnAction(e -> showSubscribersPopup(event));


        // Smart Button
        Button actionBtn = new Button();
        boolean isSubscribed = event.getSubscribers().contains(currentUser.getId());

        if (isSubscribed) {
            actionBtn.setText("Unsubscribe");
            actionBtn.setStyle("-fx-background-color: #e74c3c; -fx-text-fill: white; -fx-font-weight: bold; -fx-cursor: hand;");
            actionBtn.setOnAction(e -> handleUnsubscribe(event));
        } else {
            actionBtn.setText("Subscribe");
            actionBtn.setStyle("-fx-background-color: #27ae60; -fx-text-fill: white; -fx-font-weight: bold; -fx-cursor: hand;");
            actionBtn.setOnAction(e -> handleSubscribe(event));
        }

        actionBtn.setMaxWidth(Double.MAX_VALUE);

        card.getChildren().addAll(nameLbl, subLink, actionBtn);
        return card;
    }

    private void showSubscribersPopup(Event event) {
        if (activePopupStage != null) activePopupStage.close();

        activePopupEventId = event.getId();
        activePopupStage = new Stage();
        activePopupStage.initModality(Modality.NONE);
        activePopupStage.setTitle("Subscribers: " + event.getName());

        activePopupStage.setOnHidden(e -> {
            activePopupStage = null;
            activePopupList = null;
            activePopupEventId = null;
        });

        VBox layout = new VBox(10);
        layout.setPadding(new Insets(15));
        layout.setStyle("-fx-background-color: white;");

        Label header = new Label("Who is watching?");
        header.setFont(Font.font("System Bold", 14));

        activePopupList = new ListView<>();
        activePopupList.setPrefHeight(200);

        refreshActivePopup(event);

        layout.getChildren().addAll(header, activePopupList);

        activePopupStage.setScene(new Scene(layout, 250, 300));
        activePopupStage.show();
    }

    private void refreshActivePopup(Event freshEvent) {
        if (activePopupList == null)
            return;

        List<String> names = freshEvent.getSubscribers().stream()
                .map(id -> {
                    User u = userService.findById(id);
                    return u != null ? u.getUsername() : "Unknown ID: " + id;
                })
                .toList();

        activePopupList.setItems(FXCollections.observableArrayList(names));
    }

    private void handleSubscribe(Event event) {
        try {
            eventService.subscribe(event.getId(), currentUser.getId());
        } catch (Exception e) {
            showAlert("Failed to subscribe: " + e.getMessage());
        }
    }

    private void handleUnsubscribe(Event event) {
        try {
            eventService.unsubscribe(event.getId(), currentUser.getId());
        } catch (Exception e) {
            showAlert("Failed to unsubscribe: " + e.getMessage());
        }
    }

    private void showAlert(String msg){
        new Alert(Alert.AlertType.ERROR, msg).show();
    }

    @FXML
    public void onCreateEvent() {
        String name = newEventName.getText();
        if (name.isBlank())
            return;

        try {
            Event newEvent = eventService.createEvent(name);
            eventService.subscribe(newEvent.getId(), currentUser.getId());
            newEventName.clear();
        } catch (Exception ex) {
            showAlert("Error: " + ex.getMessage());
        }
    }

    public void cleanup() {
        if (eventService != null)
            eventService.removeObserver(this);
    }
}

//    @FXML
//    public void onDeleteEvent() {
//        Event selected = eventSelector.getValue();
//
//        try {
//            eventService.deleteEvent(selected.getId());
//            refreshEventCombo();
//        } catch (Exception ex) {
//            showAlert("Error: " + ex.getMessage());
//        }
//    }
//
//    @FXML
//    public void onSubscribe() {
//        Event selectedEvent = eventSelector.getValue();
//        User selectedUser = availableList.getSelectionModel().getSelectedItem();
//
//        if (selectedEvent == null || selectedUser == null)
//            return;
//
//        long currentEvent = selectedEvent.getId();
//
//        try {
//            eventService.subscribe(selectedEvent.getId(), selectedUser.getId());
//
//            // reset
//            refreshEventCombo();
//            restoreSelection(currentEvent);
//        } catch (Exception ex) {
//            showAlert("Error: " + ex.getMessage());
//        }
//    }
//
//    @FXML
//    public void onUnsubscribe() {
//        Event selectedEvent = eventSelector.getValue();
//        User selectedUser = subscribedList.getSelectionModel().getSelectedItem();
//
//        long currentEvent = selectedEvent.getId();
//
//        try {
//            eventService.unsubscribe(selectedEvent.getId(), selectedUser.getId());
//
//            // reset
//            refreshEventCombo();
//            restoreSelection(currentEvent);
//        } catch (Exception ex) {
//            showAlert("Error: " + ex.getMessage());
//        }
//    }
//
//    private void refreshEventCombo() {
//        eventSelector.setItems(FXCollections.observableArrayList(eventService.getAll()));
//    }
//
//    private void loadLists(Event event) {
//        // Get fresh event data
//        Event freshEvent = eventService.findById(event.getId());
//        Set<Long> subIds = freshEvent.getSubscribers();
//
//        // Get users
//        List<User> allUsers = userService.getAll();
//
//        // Split into 2 buckets
//        List<User> subs = allUsers.stream()
//                .filter(u -> subIds.contains(u.getId()))
//                .toList();
//
//        List<User> avail = allUsers.stream()
//                .filter(u -> !subIds.contains(u.getId()))
//                .toList();
//
//        // Update UI
//        subscribedList.setItems(FXCollections.observableArrayList(subs));
//        availableList.setItems(FXCollections.observableArrayList(avail));
//    }
//
//    private void restoreSelection(long eventId){
//        for(Event e : eventSelector.getItems())
//            if (e.getId() == eventId) {
//                eventSelector.getSelectionModel().select(e);
//                return;
//            }
//    }