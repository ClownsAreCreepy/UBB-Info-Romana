package scs.ui.controllers.social;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import scs.domain.interactions.Friendship;
import scs.domain.interactions.Message;
import scs.domain.user.Duck;
import scs.domain.user.User;
import scs.service.friend.FriendshipService;
import scs.service.social.MessageService;
import scs.service.social.UserService;
import scs.utilities.events.ChangeEventType;
import scs.utilities.events.EntityChangeEvent;

import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class ChatController {
    @FXML
    private Label lblUser;
    @FXML
    private ListView<User> friendsList;
    @FXML
    private VBox chatPanel;
    @FXML
    private Label headerLabel;
    @FXML
    private ListView<Message> messageList;
    @FXML
    private Label replyLabel;
    @FXML
    private TextArea inputField;

    private final ObservableList<User> friendsModel = FXCollections.observableArrayList();
    private final ObservableList<Message> messagesModel = FXCollections.observableArrayList();

    private MessageService messageService;
    private UserService userService;
    private FriendshipService friendshipService;

    private User currentUser;
    private User currentPartner;
    private Message replyTarget = null;

    public void setServices(MessageService ms, UserService us, FriendshipService fs) {
        this.messageService = ms;
        this.userService = us;
        this.friendshipService = fs;

        this.messageService.addObserver(this::onMessageEvent);
        this.friendshipService.addObserver(this::onFriendshipEvent);
        this.userService.addObserver(this::onUserEvent);

        initLogic();
    }

    private void onMessageEvent(EntityChangeEvent<Message> event) {
        if (event.type() == ChangeEventType.ADD) {
            Message msg = event.data();
            if (currentUser == null || currentPartner == null)
                return;

            long me = currentUser.getId();
            long partner = currentPartner.getId();
            long sender = msg.getFrom().getId();

            boolean incoming = (sender == partner && msg.getTo().stream().anyMatch(u -> u.getId() == me));
            boolean outgoing = (sender == me && msg.getTo().stream().anyMatch(u -> u.getId() == partner));

            boolean isBot = (sender == UserService.RACE_BOT_ID && partner == UserService.RACE_BOT_ID);

            if (incoming || outgoing || isBot)
                Platform.runLater(() -> {
                    messagesModel.add(msg);
                    messageList.scrollTo(messageList.getItems().size() - 1);
                });
        }
    }

    private void onFriendshipEvent(EntityChangeEvent<Friendship> event) {
        if (currentUser == null) return;
        Friendship f = event.data();

        if (!f.involves(currentUser.getId()))
            return;

        Platform.runLater(() -> {
            if (event.type() == ChangeEventType.ADD) {
                Long friendId = f.user1().equals(currentUser.getId()) ? f.user2() : f.user1();

                User newFriend = userService.findById(friendId);
                if (newFriend != null)
                    friendsModel.add(newFriend);
            } else if (event.type() == ChangeEventType.DELETE) {
                Long friendId = f.user1().equals(currentUser.getId()) ? f.user2() : f.user1();
                friendsModel.removeIf(u -> u.getId().equals(friendId));

                if (currentPartner != null && currentPartner.getId().equals(friendId)) {
                    chatPanel.setVisible(false);
                    currentPartner = null;
                }
            }
        });
    }

    private void onUserEvent(EntityChangeEvent<User> event) {
        Platform.runLater(() -> {
            User u = event.data();
            switch (event.type()) {
                case DELETE:
                    boolean removed = friendsModel.removeIf(friend -> friend.getId().equals(u.getId()));

                    if (removed && currentPartner != null && currentPartner.getId().equals(u.getId())) {
                        chatPanel.setVisible(false);
                        currentPartner = null;
                        messageList.getItems().clear();
                    }
                    break;

                case UPDATE:
                    for (int i = 0; i < friendsModel.size(); ++i)
                        if (friendsModel.get(i).getId().equals(u.getId())) {
                            friendsModel.set(i, u);
                            break;
                        }

                    if (currentPartner != null && currentPartner.getId().equals(u.getId())) {
                        currentPartner = u;
                        headerLabel.setText("Chat with " + u.getUsername());
                    }

                    break;
            }
        });
    }

    public void setLoggedInUser(User user) {
        this.currentUser = user;
        lblUser.setText("Your friends:");
        initialLoadFriends();
    }

    private void initLogic() {
        friendsList.setItems(friendsModel);
        messageList.setItems(messagesModel);

        // When friend selected, open chat
        friendsList.getSelectionModel().selectedItemProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal != null) {
                currentPartner = newVal;
                openChat();
            }
        });

        // When message clicked, set as reply
        messageList.getSelectionModel().selectedItemProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal != null) {
                replyTarget = newVal;
                replyLabel.setText("Replying to: " + (newVal.getText().length() > 20 ? newVal.getText().substring(0, 20) + "..." : newVal.getText()));
            }
        });

        // Formatting
        messageList.setCellFactory(param -> new ListCell<>() {
            private final Label header = new Label();
            private final Label body = new Label();
            private final VBox container = new VBox(3, header, body);

            {
                header.setStyle("-fx-font-weight: bold; -fx-text-fill: #7f8c8d; -fx-font-size: 10px");

                body.setStyle("-fx-font-size: 13px; -fx-text-fill: #2c3e50");
                body.setWrapText(true);
                body.setPadding(new Insets(0, 0, 0, 10));

                body.maxWidthProperty().bind(messageList.widthProperty().subtract(50));
            }

            @Override
            protected void updateItem(Message item, boolean empty) {
                super.updateItem(item, empty);
                if (empty || item == null) {
                    setGraphic(null);
                    setText(null);
                } else {
                    String senderName = (item.getFrom().getId().equals(currentUser.getId())) ? "ME" : item.getFrom().getUsername();
                    String time = item.getDate().format(DateTimeFormatter.ofPattern("HH:mm"));

                    String replyInfo = "";
                    if (item.getReply() != null) {
                        String quotedText = item.getReply().getText();

                        if (quotedText.length() > 30)
                            quotedText = quotedText.substring(0, 30) + "...";

                        String replyName = (item.getReply().getFrom().getId().equals(currentUser.getId())) ? "ME" : item.getReply().getFrom().getUsername();
                        replyInfo = " -> Replying to " + replyName + ": " + quotedText;
                    }

                    header.setText(senderName + " . " + time + replyInfo);
                    body.setText(item.getText());

                    setGraphic(container);
                    setText(null);
                }
            }
        });

        friendsList.setCellFactory(param -> new ListCell<>() {
            @Override
            protected void updateItem(User item, boolean empty) {
                super.updateItem(item, empty);
                if (empty || item == null)
                    setText(null);
                else
                    setText(item.getUsername() + ", id: " + item.getId() + (item instanceof Duck ? " - Duck" : " - Person"));
            }
        });
    }

    private void initialLoadFriends() {
        if (currentUser == null)
            return;

        Set<Long> friendIds = friendshipService.getFriendsOf(currentUser.getId());

        List<User> friendList = new ArrayList<>();

        if (!friendIds.isEmpty())
            friendList.addAll(userService.findUsersByIds(friendIds));

        User raceBot = userService.findById(UserService.RACE_BOT_ID);
        if (raceBot != null) {
            boolean alreadyThere = friendList.stream()
                    .anyMatch(u -> u.getId().equals(UserService.RACE_BOT_ID));

            if (!alreadyThere) {
                friendList.addFirst(raceBot);
            }
        }

        friendsModel.setAll(friendList);
    }

    private void openChat() {
        chatPanel.setVisible(true);
        headerLabel.setText("Chat with " + currentPartner.getUsername());
        onClearReply();

        List<Message> messages = messageService.getConversation(currentUser.getId(), currentPartner.getId());
        messagesModel.setAll(messages);
        messageList.scrollTo(messages.size() - 1);
    }

    @FXML
    public void onClearReply() {
        replyTarget = null;
        replyLabel.setText("Click a message to reply");
        messageList.getSelectionModel().clearSelection();
    }

    public void cleanup() {
        if (messageService != null) messageService.removeObserver(this::onMessageEvent);
        if (friendshipService != null) friendshipService.removeObserver(this::onFriendshipEvent);
        if (userService != null) userService.removeObserver(this::onUserEvent);
    }

    @FXML
    public void onSend() {
        String text = inputField.getText();
        if (text.isEmpty()) return;

        try {
            Long replyId = (replyTarget != null) ? replyTarget.getId() : null;
            messageService.sendMessage(currentUser.getId(), List.of(currentPartner.getId()), text, replyId);

            inputField.clear();
            onClearReply();
        } catch (Exception e) {
            new Alert(Alert.AlertType.ERROR, e.getMessage()).show();
        }
    }
}

//    @Override
//    public void update(EntityChangeEvent<Message> event) {
//        if (event.type() == ChangeEventType.ADD) {
//            Message msg = event.data();
//
//            if (currentUser == null || currentPartner == null)
//                return;
//
//            long me = currentUser.getId();
//            long partner = currentPartner.getId();
//            long sender = msg.getFrom().getId();
//
//            boolean amIRecipient = msg.getTo().stream().anyMatch(u -> u.getId() == me);
//            boolean isPartnerRecipient = msg.getTo().stream().anyMatch(u -> u.getId() == partner);
//
//            boolean incoming = (sender == partner && amIRecipient);
//            boolean outgoing = (sender == me && isPartnerRecipient);
//
//            if (incoming || outgoing)
//                Platform.runLater(() -> {
//                    messageList.getItems().add(msg);
//                    messageList.scrollTo(messageList.getItems().size() - 1);
//                });
//        }
//    }
//
//
//    private void refreshMessages() {
//        if (currentUser == null || currentPartner == null)
//            return;
//
//        List<Message> messages = messageService.getConversation(currentUser.getId(), currentPartner.getId());
//        messageList.setItems(FXCollections.observableArrayList(messages));
//        messageList.scrollTo(messages.size() - 1);
//    }
