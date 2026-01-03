class RationalNumber:
    # class field, will be shared by all the instances
    numberOfInstances = 0

    def __init__(self, n, m):
        """
         Initialize the rational number
         n,m - integer numbers
        """
        self.n = n
        self.m = m
        RationalNumber.numberOfInstances += 1

    @staticmethod
    def getTotalNumberOfInstances():
        """
          Get the number of instances created in the app
        """
        return RationalNumber.numberOfInstances

    @classmethod
    def fromString(cls, s):
        """
          Create a Rational numbar obiect from its string reprezentation
          cls - class
          s - string representation 1/3
        """
        parts = s.split("/")
        return RationalNumber(int(parts[0]), int(parts[1]))


def testNumberOfInstances():
    """
     test function for getTotalNumberOfInstances
    """
    assert RationalNumber.getTotalNumberOfInstances() == 0
    r1 = RationalNumber(2, 3)
    assert RationalNumber.getTotalNumberOfInstances() == 1


testNumberOfInstances()