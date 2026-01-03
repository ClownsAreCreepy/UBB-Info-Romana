def directSelectionSort(l):
    """
    sort the element of the list
    l - list of element
    return the ordered list (l[0]<l[1]<...)
    """
    for i in range(len(l)-1):
        for j in range(i+1, len(l)):
            if l[i]>l[j]:
                l[i], l[j] = l[j], l[i]