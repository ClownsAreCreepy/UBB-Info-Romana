def consistentQ(x, dim):
    # we only check the last queen (the other queens checked before)
    for i in range(len(x) - 1):    # no queen on the same column
        if x[i] == x[-1]:
            return False
    # no queen on the same diagonal
    lastX = len(x)-1
    lastY = x[-1]
    for i in range(len(x)-1):
        if abs(i - lastX) == abs(x[i] - lastY):
            return False
    return True

def solutionQ(x, dim):
    return len(x) == dim

def solutionFoundQ(x, dim):
    # print a chess board
    for column in range(dim):
        # prepare a line
        cLine = ["0"] * dim
        cLine[x[column]] = "X"
        print (" ".join(cLine))
    print ("__"*dim)

backRecQ([], 8)