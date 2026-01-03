class StudentService:
    """
      Use case coordinator for CRUD Operations on student
    """

    def __init__(self, rep, validator):
        self.rep = rep
        self.validator = validator

    def createStudent(self, id, name, adr):
        """
          store a student
          id, name, address of the student as strings
          return the Student
          raise ValueError if a student with this id already exists
          raise ValueError if the student is invalid
        """
        st = Student(id, name, adr)
        if (self.validator != None):
            self.validator.validate(st)
        self.rep.store(st)
        return st


def tesCreateStudent():
    """
      Test store student
    """
    rep = InMemoryRepository()
    val = StudentValidator()
    srv = StudentService(rep, val)
    st = srv.createStudent("1", "Ion", "Adr")
    assert st.getId() == "1"
    assert st.getName() == "Ion"
    try:
        st = srv.createStudent("1", "Vasile", "Adr")
        assert False
    except ValueError:
        pass
    try:
        st = srv.createStudent("1", "", "")
        assert False
    except ValueError:
        pass