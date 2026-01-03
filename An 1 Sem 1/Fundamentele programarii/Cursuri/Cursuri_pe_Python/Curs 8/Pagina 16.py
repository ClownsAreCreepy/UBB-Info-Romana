import unittest

class TestCaseStudentController(unittest.TestCase):
    def setUp(self):
        #code executed before every testMethod
        val=StudentValidator()
        self.ctr=StudentController(val, StudentRepository())
        st = self.ctr.create("1", "Ion", "Adr", 1, "Cluj")
    def tearDown(self):
        #cleanup code executed after every testMethod
        pass
    def testCreate(self):
        self.assertTrue(self.ctr.getNrStudents()==1)
        #test for an invalid student
        self.assertRaises(ValidationEx,self.ctr.create,"1", "", "", 1, "Cj")
        if __name__ == '__main__':
        unittest.main()
        #test for duplicated id
        self.assertRaises(DuplicatedIDException,self.ctr.create,"1", "I",
        "A", 1, "j")
    def testRemove(self):
        #test for an invalid id
        self.assertRaises(ValueError,self.ctr.remove,"2")
        self.assertTrue(self.ctr.getNrStudents()==1)
        st = self.ctr.remove("1")
        self.assertTrue(self.ctr.getNrStudents()==0)
        self.assertEquals(st.getId(),"1")
        self.assertTrue(st.getName()=="Ion")
        self.assertTrue(st.getAdr().getStreet()=="Adr")

if __name__ == '__main__':
    unittest.main()