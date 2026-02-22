package scs.ui.pages;

import javafx.scene.Parent;

public interface Page {
    Parent getView();
    void refresh();
}
