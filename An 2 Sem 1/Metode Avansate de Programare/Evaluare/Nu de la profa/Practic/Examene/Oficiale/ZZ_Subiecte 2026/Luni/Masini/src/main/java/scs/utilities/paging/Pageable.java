package scs.utilities.paging;

public class Pageable {
    private int pageNumber, pageSize;
    public Pageable(int pageNumber, int pageSize) { this.pageNumber = pageNumber; this.pageSize = pageSize; }
    public int getPageSize() { return pageSize; }
    public int getOffset() { return pageNumber * pageSize; }
}