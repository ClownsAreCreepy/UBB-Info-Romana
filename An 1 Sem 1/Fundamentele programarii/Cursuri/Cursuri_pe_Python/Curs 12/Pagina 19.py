def consistent(x):
    """
    The candidate can lead to an actual
    permutation only if there are no duplicate elements
    """
    return isSet(x)
def solution(x):
    """
    The candidate x is a solution if
    we have all the elements in the permutation
    """
    return len(x)==DIM
