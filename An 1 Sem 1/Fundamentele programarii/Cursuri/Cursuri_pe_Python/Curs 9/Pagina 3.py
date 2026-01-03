def recursiveSum(l):
    """
        Compute the sum of numbers
        l - list of number
        return int, the sum of numbers
    """
    #base case
    if l==[]:
        return 0
    #inductive step
    return l[0]+recursiveSum(l[1:])

def fibonacci(n):
    """
        compute the fibonacci number
        n - a positive integer
        return the fibonacci number for a given n
    """
    #base case
    if n==0 or n==1:
        return 1
    #inductive step
    return fibonacci(n-1)+fibonacci(n-2)