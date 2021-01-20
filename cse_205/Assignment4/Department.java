/*
Assignment #: 4
Arizona State University - CSE205
Name: Tyler Fichiera
StudentID: 1218959911
Lecture: T/Th - 4:30
Description: 
*/
package Department;

public class Department {
    // init private instance variables
    private String departmentName;
    private int numberOfMembers;
    private String university;
    private Faculty currentFaculty;

    // default constructor
    public Department() {
        // set all instance variables to their default value
        this.departmentName = "?";
        this.numberOfMembers = 0;
        this.university = "?";
        this.currentFaculty = new Faculty();
    }

    // getter method for departmentName
    public String getDeptName() {
        return this.departmentName;
    }
    
    // getter for numberOfMembers
    public int getNumberOfMembers() {
        return this.numberOfMembers;
    }

    // getter for university name
    public String getUniversity() {
        return this.university;
    }

    // getter for currentFaculty
    public Faculty getCurrentFaculty() {
        return this.currentFaculty;
    }

    // setter for departmentName
    public void setDeptName(String newDepartmentName) {
        this.departmentName = newDepartmentName;
    }

    // setter for numberOfMembers
    public void setNumberOfMembers(int newNumMembers) {
        this.numberOfMembers = newNumMembers;
    }

    // setter for university name
    public void setUniversity(String newUniversity) {
        this.university = newUniversity;
    }

    // setter for currentFaculty
    public void setCurrentFaculty(String newFirstName, String newLastName, String newLevel) {
        // init new Faculty object
        Faculty newFaculty = new Faculty();

        // set Faculty instance variables with provided replacements
        newFaculty.setFirstName(newFirstName);
        newFaculty.setLastName(newLastName);
        newFaculty.setAcademicLevel(newLevel);

        // assign new Faculty object to currentFaculty
        this.currentFaculty = newFaculty;
    }

    // convert instance variables to readable String
    public String toString() {
        // format String with useful information
        return String.format(
            "\nDepartment Name:\t\t%s\nNumber Of Members:\t%d\n" +
            "University:\t\t%s\nFaculty:\t\t%s\n\n",
            this.departmentName,
            this.numberOfMembers,
            this.university,
            this.currentFaculty
        );
    }
}