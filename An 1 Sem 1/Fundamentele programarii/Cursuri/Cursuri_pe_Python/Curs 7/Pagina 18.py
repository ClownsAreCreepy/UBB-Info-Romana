#create a validator
val = StudentValidator()
#create repository
repo = StudentFileRepository("students.txt")
#create controller and inject dependencies
srv = StudentService(val, repo)
#create Grade controller
gradeRepo = GradeFileRepository("grades.txt")
srvgr =  GradingService(gradeRepo, GradeValidator(), repo)
#create console ui and provide (inject) the controller
ui = ConsoleUI(srv, srvgr)
ui.startUI()


#create a validator
val = StudentValidator()
#create repository
repo = StudentRepository()
#create controller and inject dependencies
srv = StudentService(val, repo)
#create Grade controller
gradeRepo = GradeRepository()
srvgr =  GradingService(gradeRepo, GradeValidator(), repo)
#create console ui and provide (inject) the controller
ui = ConsoleUI(srv, srvgr)
ui.startUI()