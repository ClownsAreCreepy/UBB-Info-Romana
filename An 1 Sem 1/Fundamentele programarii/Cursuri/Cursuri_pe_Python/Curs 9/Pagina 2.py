def factorial(n):
    """
        compute the factorial
        n  is a positive integer
        return n!
    """
    if n== 0:
        return 1
    return  factorial(n-1)*n