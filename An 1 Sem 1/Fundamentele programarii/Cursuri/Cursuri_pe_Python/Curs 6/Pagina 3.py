class RationalNumber:
    def __init__(self, a, b):
        """
        Initialize a rational number
        a,b integer numbers
        """
        self.__nr = [a, b]
    def getDenominator(self):
        """
        Getter method return the denominator
        """
        return self.__nr[1]
    def getNominator(self):
        """"
        Getter method return the nominator
        """
        return self.__nr[0]
    def add(self, a):
        pass