def backtracking(x,DIM):
    if len(x)==DIM:
        print (x)
        return  #stop recursion
    x.append(0)
    for i in range(0,DIM):
        x[-1] = i
        if isSet(x):
            #continue only if x can conduct to a solution
            backtracking(x,DIM)
    x.pop()

backtracking([], 3)