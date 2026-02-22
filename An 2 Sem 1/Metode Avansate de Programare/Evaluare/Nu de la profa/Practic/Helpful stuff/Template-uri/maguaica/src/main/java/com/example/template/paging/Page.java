package com.example.template.paging;

public class Page<E> {
    private Iterable<E> elementsOnPage;
    private int totalNumberElements;

    public Page(int totalNumberElements,Iterable<E> elementsOnPage) {
        this.elementsOnPage = elementsOnPage;
        this.totalNumberElements = totalNumberElements;
    }

    public Iterable<E> getElementsOnPage() {
        return elementsOnPage;
    }

    public int getTotalNumberElements() {
        return totalNumberElements;
    }


}
