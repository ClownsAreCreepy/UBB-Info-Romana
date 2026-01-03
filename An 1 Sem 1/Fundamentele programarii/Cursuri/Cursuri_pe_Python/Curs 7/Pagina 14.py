def store(self, gr):
    """
        Store a grade
        post: grade is in the repository
        raise GradeAlreadyAssigned exception if we already have a grade
        for the student at the given discipline
        raise RepositoryException if there is an IO error when writing to
        the file
    """
    if self.find(gr.getStudent(), gr.getDiscipline())!=None:
        raise GradeAlreadyAssigned()
    #open the file for append
    try:
        f = open(self.__fname, "a")
        grStr = gr.getStudent().getId()+","+gr.getDiscipline()
        grStr =grStr+","+str(gr.getGrade())+"\n"
        f.write(grStr)
        f.close()
    except IOError:
        raise RepositorException("Unable to write a grade to the file")
