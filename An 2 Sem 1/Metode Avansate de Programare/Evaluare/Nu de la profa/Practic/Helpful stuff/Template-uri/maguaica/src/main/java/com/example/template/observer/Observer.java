package com.example.template.observer;


import com.example.taximetrie.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}