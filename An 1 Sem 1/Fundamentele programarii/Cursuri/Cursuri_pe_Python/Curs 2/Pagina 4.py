 #Varianta nunu:
def f(k):
    l = 2
    while l<k and k % l>0:
            l=l+1
    return l>=k

    #Varianta acceptata:
def isPrime(nr):
    """
      Verify if a number is prime
      nr - integer number, nr>1
      return True if nr is prime, False otherwise
    """
    div = 2  #search for divider starting from 2
    while div<nr and nr % div>0:
        div=div+1
    #if the first divider is the number itself than the number is prime
    return div>=nr