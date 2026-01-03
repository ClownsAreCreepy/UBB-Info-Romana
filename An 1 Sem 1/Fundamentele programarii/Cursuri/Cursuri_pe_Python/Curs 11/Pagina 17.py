lambda x:x+7

def f(x):
    return x+7
print ( f(5) )

print ( (lambda x:x+7)(5) )

l = []
l.append(MyClass(2,"a"))
l.append(MyClass(7,"d"))
l.append(MyClass(1,"c"))
l.append(MyClass(6,"b"))
#sort on name
ls = sorted(l,key=lambda o:o.name)
for x in ls:
    print (x)

l = []
l.append(MyClass(2,"a"))
l.append(MyClass(7,"d"))
l.append(MyClass(1,"c"))
l.append(MyClass(6,"b"))
#sort on id
ls = sorted(l,key=lambda o:o.id)
for x in ls:
    print (x)