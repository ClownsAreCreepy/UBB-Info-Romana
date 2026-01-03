def change_or_not_immutable(a):
    print ('Locals ', locals())
    print ('Before assignment: a = ', a, ' id = ', id(a))
    a = 0
    print ('After assignment: a = ', a, ' id = ', id(a))
g1 = 1      #global immutable int
#Mine: print ('Globals ', globals())
#Mine: print ('Before call: g1 = ', g1, ' id = ', id(g1))
#Mine: change_or_not_immutable(g1)
#Mine: print ('After call: g1 = ', g1, ' id = ', id(g1))


def change_or_not_mutable(a):
    print ('Locals ', locals())
    print ('Before assignment: a = ', a, ' id = ', id(a))
    a[1] = 1
    a = [0]
    print ('After assignment: a = ', a, ' id = ', id(a))
g2 = [0, 1] #global mutable list
#Mine: print ('Globals ', globals())
#Mine: print ('Before call: g2 = ', g2, ' id = ', id(g2))
#Mine: change_or_not_mutable(g2)
#Mine: print ('After call: g2 = ', g2, ' id = ', id(g2))