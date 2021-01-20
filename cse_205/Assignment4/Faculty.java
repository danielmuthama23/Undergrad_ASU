/*
Assignment #: 4
Arizona State University - CSE205
Name: Tyler Fichiera
StudentID: 1218959911
Lecture: T/Th - 4:30
Description: 
*/
package Faculty;

public class Faculty {
    // init private instance variables
    private String firstName;
    private String lastName;
    private String academicLevel;

    // default constructor
    public Faculty() {
        // set all String instance variables to "?"
        this.firstName = "?";
        this.lastName = "?";
        this.academicLevel = "?";
    }

    // getter for firstName
    public String getFirstName() {
        return this.firstName;
    }

    // getter for lastName
    public String getLastName() {
        return this.lastName;
    }

    // getter for academicLevel
    public String getAcademicLevel() {
        return this.academicLevel;
    }

    // setter for firstName
    public void setFirstName(String newFirstName) {
        this.firstName = newFirstName;
    }

    // setter for lastName
    public void setLastName(String newLastName) {
        this.lastName = newLastName;
    }

    // setter for academicLevel
    public void setAcademicLevel(String newAcademicLevel) {
        this.academicLevel = newAcademicLevel;
    }

    // convert instance variables to readable String
    public String toString() {
        // format String with useful information
        return String.format("%s,%s(%s)", this.lastName, this.firstName, this.academicLevel);
    }
}