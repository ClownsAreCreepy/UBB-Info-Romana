# Tuples are immutable sequences
# A tuple consists of a number
# of values separated by commas

# tuple packing
t = 12, 21, 'ab'
#Mine:print(t[0])

# empty tuple (0 items)
empty = ()


# sequence unpacking
x, y, z = t
#Mine:print(x, y, z)


# tuple with one item
singleton = (12,)
#Mine:print(singleton)
#Mine:(len(singleton))

# tuple in a for
#Mine:t = 1, 2, 3
for el in t:
    pass
    #Mine:print(el)


# Tuples may be nested
u = t, (23, 32)
#Mine:print(u)