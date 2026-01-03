def __add__(self,other):
    """
    Overload + operator
    other  - rational number
    return a rational number,
    the sum of self and other
    """
    return self.add(other)


def testAddOperator():
    """
    Test function for the + operator
    """
    r1 = RationalNumber(1,3)
    r2 = RationalNumber(1,3)
    r3 = r1+r2
    assert r3 == RationalNumber(2,3)