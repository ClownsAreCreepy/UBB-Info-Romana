class A:
    def __init__(self):
        print("Initialise A")

    def f(self):
        print("in method f from A")

    def g(self):
        print("in method g from A")


class B(A):
    """
      This class extends A
      A is the base class,
      B is the derived class
      B is inheriting everything from class A
    """

    def __init__(self):
        # initialise the base class
        A.__init__(self)
        print ("Initialise B")

    def g(self):
        """
          Overwrite method g from A
        """
        # we may invoke the function from the base class
        A.f(self)
        print("in method g from B")

b = B()
#f is inherited from A
b.f()
b.g()