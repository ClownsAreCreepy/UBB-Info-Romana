def testCreate():
    """
      Test function for creating rational numbers
    """
    r1 = RationalNumber(1, 3)  # create the rational number 1/3
    assert r1.getNominator() == 1
    assert r1.getDenominator() == 3
    r1 = RationalNumber(4, 3)  # create the rational number 4/3
    assert r1.getNominator() == 4
    assert r1.getDenominator() == 3


class RationalNumber:
    """
      Abstract data type rational numbers
      Domain: {a/b  where a,b integer numbers, b!=0, greatest common divisor
a, b =1}
    """

    def __init__(self, a, b):
        """
          Initialize a rational number
          a,b integer numbers
        """
        self.__nr = [a, b]

    def getDenominator(self):
        """
           Getter method
           return the denominator of the rational number
        """
        return self.__nr[1]

    def getNominator(self):
        """"
          Getter method
          return the nominator of the method
        """
        return self.__nr[0]