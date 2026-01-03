def filterScoreUI():
    st = input("Start sc:")
    end = input("End sc:")
    rez = filterScore(l, st, end)
    for e in rez:
        print(e)


def filterScore(l, st, end):
    """
    filter participants
    l - list of participants
    st, end - integers -scores
    return list of participants
        filtered by st end score
    """
    rez = []
    for p in l:
        if getScore(p) > st and getScore(p) < end:
            rez.append(p)
    return rez


def testScore():
 l = [["Ana", 100]]
 assert filterScore(l,10,30)==[]
 assert filterScore(l,1,30)==l
 l = [["Ana", 100],["Ion", 40],["P", 60]]
 assert filterScore(l,3,50)==[["Ion", 40]]