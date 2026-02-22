package ui;

import javafx.event.ActionEvent;

public class MainController {
    public void onListUsers(ActionEvent e){
        System.out.println("List users pressed");
    }

    public void onShowCommunities(ActionEvent e){
        System.out.println("Show communities pressed");
    }

    public void onExit(ActionEvent e) {
        System.exit(0);
    }
}
