def f():
    #   x = 1/0
    raise ValueError("Error Message") #   aruncăm excepție
try:
    f()
except ValueError as msg:
    print ("handle value error:", msg)
except KeyError:
    print ("handle key error")
except:
    print ("handle any other errors")
finally:
    print ("Clean-up code here")