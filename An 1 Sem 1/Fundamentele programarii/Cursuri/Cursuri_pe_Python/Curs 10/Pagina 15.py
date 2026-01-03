sw = StopWatch()
poz = searchBinaryRec(e, l)
print("    BinaryRec in %f sec; poz=%i" % (sw.stop(), poz))


def measurePythonIndex(e, l):
    sw = StopWatch()
    poz = -2
    try:
        poz = l.index(e)
    except ValueError:
        pass  # we ignore the error..
    print("    PythIndex in %f sec; poz=%i" % (sw.stop(), poz))


def measureSearchSeq(e, l):
    sw = StopWatch()
    poz = searchSeq(e, l)
    print("    searchSeq in %f sec; poz=%i" % (sw.stop(), poz))