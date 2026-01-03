def greedy(c):
    """
       Greedy algorithm
       c - a list of candidates
       return a list (B) the solution found (if exists) using the greedy
strategy, None if the algorithm
       selectMostPromissing - a function that return the most promising
candidate
       acceptable - a function that returns True if a candidate solution can be
extended to a solution
       solution - verify if a given candidate is a solution
    """
    b = []  # start with an empty set as a candidate solution
    while not solution(b) and c != []:
        # select the local optimum (the best candidate)
        candidate = selectMostPromissing(c)
        # remove the current candidate
        c.remove(candidate)
        # if the new extended  candidate solution is acceptable
        if acceptable(b + [candidate]):
            b.append(candidate)

    if solution(b):
        return b
        # there is no solution
    return None