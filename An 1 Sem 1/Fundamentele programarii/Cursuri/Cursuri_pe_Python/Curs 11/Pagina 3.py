def bubbleSort(l):
    sorted = False
    while not sorted:
        sorted = True
        for i in range(len(l) - 1):
            if l[i+1] < l[i]:
                l[i], l[i+1] = l[i+1], l[i]
                sorted = False

def bubbleSort2(l):
    for i in range(1, len(l)):
        for j in range(len(l)-i):
            if l[j] > l[j+1]:
                l[j], l[j+1] = l[j+1], l[j]
        print(l)

