def store(self, st):
    """
      Store the student to the file.Overwrite store
      st - student
      Post: student is stored to the file
      raise DuplicatedIdException for duplicated id
    """
    StudentRepository.store(self, st)
    self.__storeToFile()


def __storeToFile(self):
    """
     Store all the students  in to the file
     raise CorruptedFileException if we can not store to the file
    """
    f = open(self.__fName, "w")
    sts = StudentRepository.getAll(self)
    for st in sts:
        strf = st.getId() + ";" + st.getName() + ";"
        strf = strf + st.getAdr().getStreet() + ";" + str(st.getAdr().getNr()) +";" + st.getAdr().getCity()
        strf = strf + "\n"
        f.write(strf)
    f.close()


def testStore():
    fileName = "teststudent.txt"
    repo = StudentFileRepository(fileName)
    repo.removeAll()

    st = Student("1", "Ion", Address("str", 3, "Cluj"))
    repo.store(st)
    assert repo.size() == 1
    assert repo.find("1") == st
    # verify if the student is stored in the file
    repo2 = StudentFileRepository(fileName)
    assert repo2.size() == 1
    assert repo2.find("1") == st