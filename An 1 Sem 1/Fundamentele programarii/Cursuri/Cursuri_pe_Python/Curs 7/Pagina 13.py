gr = ctr.assign("1", "FP", 10)
assert gr.getDiscipline()=="FP"
assert gr.getGrade()==10
assert gr.getStudent().getId()=="1"
assert gr.getStudent().getName()=="Ion"

st = Student("1", "Ion",
Address("Adr", 1, "Cluj"))
rep = GradeRepository()
grades = rep.getAll(st)
assert grades[0].getStudent()==st
assert grades[0].getGrade()==10
