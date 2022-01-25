class Person:
  def __init__(self, fname, lname):
    self._firstname = fname
    self._lastname = lname

  def printname(self):
    print(self._firstname, self._lastname)

class Adult:
    def __init__(self, name0 = "Edwin", name1 = "Wang", gender = "non-binary", married = False):
        if gender.lower() == "male":
            self._lname = "Mr. " + name1
        elif gender.lower() == "female":
            self._lname = "Ms. " + name1
        else:
            self._lname = "Mx. " + name1
        self._fname = name0

    def printname(self):
        print(self._lname)

class Student(Person):
    pass # Use the pass keyword when you do not want to add any other properties or methods to the class. 

class Professor(Person, Adult):
    pass # Use the pass keyword when you do not want to add any other properties or methods to the class. 

# TODO: Create a person class and call its printname function
# TODO: Create a student class and call its printname function

# Replace this comment with your code for the above TODOs

# BEFORE YOU CREATE A PROFESSOR CLASS, What do you think it'll print when we call its printname function?
# Replace this comment with your answer to the above question

# TODO: Create a professor class and call its printname function

# What happened to the professor? Which printname did it use?
# Replace this comment with your answer to the above question

# Why might the professor may have used the printname that it did?
# Replace this comment with your answer to the above question

# Do we remember what the underscore before a variable name means?
# Replace this comment with your answer to the above question

# What if we put two underscores before a method name? (If you don't remember, try it)
# Replace this comment with your answer to the above question