class RationalNumber:
    """
    Abstract data type for rational numbers
    Domain: {a/b where a and b are integer numbers b!=0}
    """
    def __init__(self, a, b):
        """
        Creates a new instance of RationalNumber
        """
        #create a field in the rational number
        #every instance (self) will have this field
        self.n = a
        self.m = b

x = RationalNumber(1,3)
y = RationalNumber(2,3)
x.m = 7
x.n = 8
y.m = 44
y.n = 21