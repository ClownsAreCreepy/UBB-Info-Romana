"""
   Abstract data type for rational numbers
   Domain: {a/b where a and b are integer numbers b!=0}
"""
# class field, will be shared by all the instances
numberOfInstances = 0


def __init__(self, a, b):
    """
      Creates a new instance of RationalNumber
    """
    self.n = a
    self.m = b
    RationalNumber.numberOfInstances += 1  # accessing class fields


def testNumberInstances():
    assert RationalNumber.numberOfInstances == 0
    r1 = RationalNumber(1, 3)
    # show the class field numberOfInstances
    assert r1.numberOfInstances == 1
    # set numberOfInstances from the class
    r1.numberOfInstances = 8
    assert r1.numberOfInstances == 8  # access to the instance field
    assert RationalNumber.numberOfInstances == 1  # access to the class field


testNumberInstances()