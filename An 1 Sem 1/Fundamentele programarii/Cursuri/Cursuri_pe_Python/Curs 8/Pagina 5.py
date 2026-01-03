class StudentFileRepository(StudentRepository):
    """
      Store/retrieve students from file
    """

    def __init__(self, fileN):
        # properly initialise the base class
        StudentRepository.__init__(self)
        self.__fName = fileN
        # load student from the file
        self.__loadFromFile()

    def __loadFromFile(self):
        """
          Load students from file
          raise ValueError if there is an error when reading from the file
        """
        try:
            f = open(self.__fName, "r")
        except IOError:
            # file not exist
            return
        line = f.readline().strip()
        while line != "":
            attrs = line.split(";")
            st = Student(attrs[0], attrs[1], Address(attrs[2], attrs[3], attrs[4]))
            StudentRepository.store(self, st)
            line = f.readline().strip()
        f.close()