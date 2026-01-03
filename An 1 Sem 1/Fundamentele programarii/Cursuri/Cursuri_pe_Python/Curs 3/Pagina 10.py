#Exemplu rau >:(
def verify(k):
    """
    Verify if a number is prime
    nr - integer number, nr>1
    return True if nr is prime
    """
    l = 2
    while l<k and k % l>0:
        l=l+1
    return l>=k

#Exemplu bun :D
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