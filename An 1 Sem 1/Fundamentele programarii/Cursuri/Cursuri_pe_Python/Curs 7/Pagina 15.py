def getAllForDisc(self, disc):
    """
     Return all the grades for all the students from all disciplines
     disc - string, the discipline
     return list of StudentGrade's
    """
    try:
        f = open(self.__fname, "r")
    except IOError:
        # the file is not created yet
        return None
    try:
        rez = []  # StudentGrade instances
        line = f.readline().strip()
        while line != "":
            attrs = line.split(",")
            # if this line refers to the requested student
            if attrs[1] == disc:
                gr = StudentGrade(attrs[0], attrs[1], float(attrs[2]))
                rez.append(gr)
            line = f.readline().strip()
        f.close()
        return rez
    except IOError:
        raise RepositorException("Unable to read grades from the file")