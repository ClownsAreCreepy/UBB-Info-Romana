def generateAndTest(x,DIM):
    if len(x)==DIM and isSet(x):
        print (x)
    if len(x)>DIM:
        return
    x.append(0)
    for i in range(0,DIM):
        x[-1] = i
        generateAndTest(x,DIM)
    x.pop()

generateAndTest([],3)