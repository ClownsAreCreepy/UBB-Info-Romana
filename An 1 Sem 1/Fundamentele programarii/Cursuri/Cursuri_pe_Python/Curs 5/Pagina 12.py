def __str__(self):
    """
      provide a string representation for the rational number
      return a string
    """
    return str(self.__nr[0]) + "/" + str(self.__nr[1])


def testCompareOperator():
    """
    Test function for < >
    """
    r1 = RationalNumber(1, 3)
    r2 = RationalNumber(2, 3)
    assert r2>r1
    assert r1<r2


def __lt__(self, ot):
    """
      Compare 2 rational numbers (less than)
      self the current instance
      ot a rational number
      return True if self<ot,False otherwise
    """
    if self.getFloat() < ot.getFloat():
        return True
    return False


def __eq__(self, other):
    """
    Verify if 2 rational are equals
    other - a rational number
    return True if the instance is
equal with other
     """
    return self.__nr == other.__nr


def testEqual():
    """
      test function for ==
    """
    r1 = RationalNumber(1, 3)
    assert r1==r1
    r2 = RationalNumber(1, 3)
    assert r1==r2
    r1 = RationalNumber(1, 3)
    r1 = r1.add(RationalNumber(2, 3))
    r2 = RationalNumber(1, 1)
    assert r1==r2