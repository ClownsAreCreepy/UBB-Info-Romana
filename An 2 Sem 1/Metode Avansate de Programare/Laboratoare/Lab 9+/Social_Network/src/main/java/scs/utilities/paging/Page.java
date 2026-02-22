package scs.utilities.paging;

import java.util.List;
import java.util.stream.Stream;

public class Page<E> {
    private final List<E> elements;
    private final int totalElementCount;
    private final int pageSize;


    public Page(List<E> elements, int totalElementCount, int pageSize) {
        this.elements = elements;
        this.totalElementCount = totalElementCount;
        this.pageSize = pageSize;
    }

    public List<E> getElementsOnPage() {
        return elements;
    }

    public int getTotalElementCount() {
        return totalElementCount;
    }

    public int getCurrentPageSize() {
        return elements.size();
    }

    public int getTotalPages() {
        if (totalElementCount == 0 || pageSize == 0) return 0;
        return (int) Math.ceil((double) totalElementCount / pageSize);
    }

    public Stream<E> stream() {
        return elements.stream();
    }
}
