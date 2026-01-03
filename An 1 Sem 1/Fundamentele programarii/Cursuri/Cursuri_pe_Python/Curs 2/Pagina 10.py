a = 100
def f():
    a = 300
    print (a)
#Mine: f()
#Mine: print (a)

#paralel

a = 100
def f():
    global a
    a =300
    print (a)
#Mine: f()
#Mine: print (a)

a = 300
def f():
    a = 500
    print (a)
    print (locals())
    print (globals())
#Mine: f()
#Mine: print (a)