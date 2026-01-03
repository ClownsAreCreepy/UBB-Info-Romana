class StudentValidator:
    """
        Class responsible with validation
    """
    def validate(self, st):
        """
        Validate a student
        st - student
        raise ValueError
        if: Id, name or address is empty
        """
        errors = ""
        if (st.id==""):
            errors+="Id can not be empty;"
        if (st.name==""):
            errors+="Name can not be empty;"
        if (st.adr==""):
            errors+="Address can not be empty"
        if len(errors)>0:
            raise ValueError(errors)


def testStudentValidator():
    """
        Test validate
    """
    validator = StudentValidator()
    st = Student("", "Ion", "str")
    try:
        validator.validate(st)
        assert False
    except ValueError:
        assert True
    st = Student("", "", "")
    try:
        validator.validate(st)
        assert False
    except ValueError:
        assert True