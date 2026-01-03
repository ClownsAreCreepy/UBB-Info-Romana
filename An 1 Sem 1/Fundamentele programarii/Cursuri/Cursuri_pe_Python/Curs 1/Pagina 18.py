def gcd(a, b):
    """
    Return the greatest common divisor of two positive integers.
    """
    if a == 0: return b
    if b == 0: return a

    while a != b:
        if a > b:
            a = a - b
        else:
            b = b - a
    return a

print(gcd(7, 15))