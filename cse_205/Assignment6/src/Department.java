// Assignment #: 6
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: The class that handles all Department objects

public class Department {
      // init instance vars
      private String name;
      private int numberOfFaculty;
      private String university;

      // default constructor
      public Department() {
            name = "?";
            numberOfFaculty = 0;
            university = "?";
      }

      // constructor with args that are added as instance vars
      public Department(String name, int numberOfFaculty, String university) {
            this.name = name;
            this.numberOfFaculty = numberOfFaculty;
            this.university = university;
      }

      // accesssor method for name
      public String getDeptName() {
            return name;
      }
      
      // accesssor method for numberOfFaculty
      public int getNumberOfMembers() {
            return numberOfFaculty;
      }

      // accessor method for university
      public String getUniversity() {
            return university;
      }

      // mutator method for name
      public void setDeptName(String name) {
            this.name = name;
      }

      // mutator method for numberOfFaculty
      public void setNumberOfMembers(int numFaculty) {
            this.numberOfFaculty = numFaculty;
      }
      
      // mutator method for university
      public void setUniversity(String name) {
            this.university = name;
      }

      // default toString method
      public String toString() {
            return "\nDepartment Name:\t\t" + name + "\nNumber Of Faculty:\t" + numberOfFaculty +
                        "\nUniversity:\t\t" + university + "\n\n";
      }
}

