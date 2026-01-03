def getTop5(self, disc):
    """
      Get the best 5 students at a given discipline
      disc - string, discipline
      return list of StudentGrade ordered descending on the grade
    """
    sds = self.__grRep.getAllForDisc(disc)
    # order based on the grade
    sortedsds = sorted(sds, key=lambda studentGrade:
    studentGrade.getGrade(), reverse=True)
    # retain only the first 5
    sortedsds = sortedsds[:5]
    # obtain the student names
    for sd in sortedsds:
        st = self.__stRep.find(sd.getStudentID())
        sd.setStudentName(st.getName())
    return sortedsds