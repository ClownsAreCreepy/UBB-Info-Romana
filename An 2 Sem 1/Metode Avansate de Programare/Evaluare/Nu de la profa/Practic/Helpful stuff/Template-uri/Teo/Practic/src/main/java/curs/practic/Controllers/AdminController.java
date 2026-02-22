package curs.practic.Controllers;

import curs.practic.Service.Service;
import curs.practic.Util.event.EntityChangeEvent;
import curs.practic.Util.event.EntityChangeEventType;
import curs.practic.Util.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

public class AdminController implements Observer<EntityChangeEvent<?>> {
//    public TableColumn columnId;
//    public TableView mainTable;
    private Service service;

//    private final ObservableList<> model = FXCollections.observableArrayList();

    public void setService(Service service){
        this.service = service;
        service.addObserver(this);
        init();
    }

    public void init(){
//        model.clear();
        //service.getOrders().forEach(model::add);

//        for(elem el: service.getall()){
//            model.add(el);
//        }

//        mainTable.setItems(model);
    }

    @FXML
    public void initialize() {
//        columnId.setCellValueFactory(new PropertyValueFactory<>("id"));
//        mainTable.setItems(model);
    }


    @Override
    public void update(EntityChangeEvent<?> entityChangeEvent) {
//        if (entityChangeEvent.getType().equals(EntityChangeEventType.ADD)){
//            init();
//        }
    }
}
