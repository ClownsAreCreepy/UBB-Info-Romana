#Varianta zaz
def applyToFile(fileName):
    """
      process file line by line
    """
    fh = open(fileName)
    for line in fh:
        processLine(line)
    fh.close()


#Varianta good
def applyToFile(fileName):
    """
      process file line by line
    """
    fh = open(fileName)
    try:
        for line in fh:
            processLine(line)
    finally:
        fh.close()


#Varianta Hella Good
def applyToFile(fileName):
    """
      process file line by line
    """
    with open(fileName) as fh:
        for line in fh:
            processLine(line)