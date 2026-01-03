def mergeSort(l, start, end):
    """
    sort the element of the list
    l - list of element
    return the ordered list (l[0]<l[1]<...)
    """
    if end-start <= 1:
        return
    m = (end + start) // 2
    mergeSort(l, start, m)
    mergeSort(l, m, end)
    merge(l, start, end, m)

mergeSort([], 0, 1)