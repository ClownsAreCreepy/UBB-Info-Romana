# create
a = [1, 2, 'a']
#Mine:print(a)
x, y, z = a
#Mine:print(x, y, z)


# indices: 0, 1, ..., len(a) – 1
#Mine:print(a[0])
#Mine:print('last element = ', a[len(a) - 1])

# lists are mutable
a[1] = 3
#Mine:print(a)


# lists as stacks
stack = [1, 2, 3]
stack.append(4)
#Mine:print(stack)
#Mine:print(stack.pop())
#Mine:print(stack)


# generate lists using range
l1 = range(10)
#Mine:print(list(l1))
l2 = range(0, 10)
#Mine:print(list(l2))
l3 = range(0, 10, 2)
#Mine:print(list(l3))
l4 = list(range(9, 0, -1))
#Mine:print(l4)


# slicing
#Mine:print(a[:2])
b = a[:]
#Mine:print(b)
b[1] = 5
#Mine:print(b)
a[3:] = [7, 9]
#Mine:print(a)
a[:0] = [-1]
#Mine:print(a)
a[0:2] = [-10, 10]
#Mine:print(a)


# nesting
a = [1, [1, 1, 9], 9]
#Mine:print(a)
b = [1, 1, 9]
c = [1, b, 9]
#Mine:print(c)


# list in a for loop
l = range(0, 10)
for i in l:
    pass
    #Mine:print(i)
