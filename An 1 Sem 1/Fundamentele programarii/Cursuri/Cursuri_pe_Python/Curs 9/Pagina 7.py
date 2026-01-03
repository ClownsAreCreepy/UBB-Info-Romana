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

def fibonacci2(n):
    """
     compute the fibonacci number
     n - a positive integer
     return the fibonacci number for a given n
    """
    sum1 = 1
    sum2 = 1
    rez = 0
    for i in range(2, n+1):
        rez = sum1+sum2
        sum1 = sum2
        sum2 = rez
    return rez


def measureFibo(nr):
    sw = StopWatch()
    print
    "fibonacci2(", nr, ") =", fibonacci2(nr)
    print
    "fibonacci2 take " + str(sw.stop()) + " seconds"

    sw = StopWatch()
    print
    "fibonacci(", nr, ") =", fibonacci(nr)
    print
    "fibonacci take " + str(sw.stop()) + " seconds"


measureFibo(32)