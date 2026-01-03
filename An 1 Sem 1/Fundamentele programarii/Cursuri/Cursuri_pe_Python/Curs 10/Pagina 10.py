def searchBinaryNonRec(el, l):
    """
      Search an element in a list
      el - element to be searched
      l - a list of ordered elements
      return the position of first occurrence or the position where the element can be inserted
    """
    if len(l) == 0:
        return 0
    if el<=l[0]:
        return l[0]
    if el>=l[len(l)-1]:
        return len(l)-1
    right = len(l)-1
    left = 0
    while right - left > 1:
        m = (left + right)//2
        if el<=l[m]:
            right = m
        else:
            left = m
    return right