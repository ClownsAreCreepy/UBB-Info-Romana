def quickSort(list):
    """
        Quicksort using list comprehensions
        return a new list
    """
    if len(list) <= 1:
        return list
    pivot = list.pop()
    lesser = quickSort([x for x in list if x < pivot])
    greater = quickSort([x for x in list if x >= pivot])
    return lesser + [pivot] + greater

l = [124,124,21,423,624,35,753,7,45,746,86,759,47,436,25,253,35]
print(quickSort(l))
