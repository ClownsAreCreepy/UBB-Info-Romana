def test_gcd():
    assert gcd(2, 3) == 1
    assert gcd(2, 4) == 2
    assert gcd(6, 4) == 2
    assert gcd(0, 2) == 2
    assert gcd(2, 0) == 2
    assert gcd(24, 9) == 3

def gcd(a, b):
    """
     Compute the greatest common divisor of two positive integers
     a, b integers a,b >=0
     Return the greatest common divisor of two positive integers.
    """
    if a == 0:
        return b
    if b == 0:
        return a
    while a != b:
       if a > b:
           a = a - b
       else:
           b = b - a
    return a
