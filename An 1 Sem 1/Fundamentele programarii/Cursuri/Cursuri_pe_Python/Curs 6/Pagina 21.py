class InMemoryRepository:
    """
     Manage the store/retrieval of students
    """

    def __init__(self):
        self.students = {}

    def store(self, st):
        """
          Store students
          st is a student
          raise RepositoryException if we have a student with the same id
        """
        if st.getId() in self.students:
            raise ValueError("A student with this id already exist")

        if (self.validator != None):
            self.validator.validate(st)

        self.students[st.getId()] = st


def testStoreStudent():
    st = Student("1", "Ion", "Adr")
    rep = InMemoryRepository()
    assert rep.size()==0
    rep.store(st)
    assert rep.size()==1
    st2 = Student("2", "Vasile", "Adr2")
    rep.store(st2)
    assert rep.size()==2
    st3 = Student("2", "Ana", "Adr3")
    try:
        rep.store(st3)
        assert False
    except ValueError:
        pass