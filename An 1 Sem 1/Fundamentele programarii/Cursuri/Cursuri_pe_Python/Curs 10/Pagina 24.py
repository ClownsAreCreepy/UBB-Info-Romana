def insertSort(l):
    """
        sort the elements of the list
        l - list of element
        return the ordered list (l[0]<l[1]<...)
    """
    for i in range(1, len(l)):
        ind = i - 1
        a = l[i]
        #insert a in the right position
        while ind>=0 and a<l[ind]:
            l[ind+1] = l[ind]
            ind = ind - 1
        l[ind+1] = a
        print(l)