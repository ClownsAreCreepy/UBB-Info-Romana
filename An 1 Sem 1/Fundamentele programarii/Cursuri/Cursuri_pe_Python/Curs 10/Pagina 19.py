def selectionSort(l):
    """
    sort the element of the list
    l - list of element
    return the ordered list (l[0]<l[1]<...)
    """
    for i in range(len(l)):
        index = i
        for j in range(i+1,len(l)):
            if (l[j]<l[index]):
                index = j
        if (i<index):
            aux = l[i]
            l[i] = l[index]
            l[index] = aux