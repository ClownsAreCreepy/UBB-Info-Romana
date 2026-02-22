package com.example.template.events;


import com.example.taximetrie.domeniu.Comanda;

public class UtilizatorEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Comanda data, oldData;

    public UtilizatorEntityChangeEvent(ChangeEventType type, Comanda data) {
        this.type = type;
        this.data = data;
    }
    public UtilizatorEntityChangeEvent(ChangeEventType type, Comanda data, Comanda oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Comanda getData() {
        return data;
    }

    public Comanda getOldData() {
        return oldData;
    }

    public ChangeEventType getEventType() {
        return type;
    }
}