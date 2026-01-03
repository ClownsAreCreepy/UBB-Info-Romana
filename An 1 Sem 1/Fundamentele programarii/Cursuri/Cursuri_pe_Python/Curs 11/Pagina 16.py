l = sorted([1,7,3,2,5,4])
print(l)

l.sort(reverse=True)
print(l)

l.sort()
print(l)

l = sorted([1,7,3,2,5,4],reverse=True)
print(l)

def keyF(o1):
    return o1.name

ls = sorted([1,7,3,2,5,4],keyF)