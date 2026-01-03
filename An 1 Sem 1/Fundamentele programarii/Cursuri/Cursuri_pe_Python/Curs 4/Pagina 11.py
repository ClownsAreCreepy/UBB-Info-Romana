# Ui
def filterScoreUI():  # manage the user interaction
    st = input("Start sc:")
    end = input("End sc:")
    rez = filterScoreDomain(st, end)
    for e in rez:
        print(e)

# domain
all = [["Ion", 50], ["Ana", 30], ["Pop", 100]]
def filterScoreDomain(all, st, end):  # filter the score board
    if end < st: return []
    rez = filterMatrix(l, 1, st, end)
    return rez


# Utility function - infrastructure
def filterMatrix(matrice, col, st, end):  # filter matrix lines
    linii = []
    for linie in matrice:
        if linie[col] > st and linie[col] < end:
            linii.append(linie)
    return linii