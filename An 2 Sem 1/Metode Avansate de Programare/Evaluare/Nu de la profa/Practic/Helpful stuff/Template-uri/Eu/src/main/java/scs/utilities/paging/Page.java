package scs.utilities.paging;

import java.util.List;

public class Page<E> {
    private List<E> elements;
    private int totalElementCount;

    public Page(List<E> elements, int total, int size) { this.elements = elements; this.totalElementCount = total; }
    public List<E> getElementsOnPage() { return elements; }
    public int getTotalElementCount() { return totalElementCount; }
}