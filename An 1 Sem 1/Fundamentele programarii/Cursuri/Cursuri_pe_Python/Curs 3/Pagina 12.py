#Unde incepem

def isPrime(nr):
    """
    Verify if a number is prime
    nr - integer number, nr>1
    return True if nr is prime
    """
    for div in range(2,nr):
        if nr%div == 0:
            return False
    return True



#Unde ajungem

def isPrime(nr):
    """
    Verify if a number is prime
    nr - integer number, nr>1
    return True if nr is prime
    """
    div = 2  #search for divider
    while div<nr and nr % div>0:
        div=div+1
    #if the first divider is the number itself than nr is prime
    return div>=nr;