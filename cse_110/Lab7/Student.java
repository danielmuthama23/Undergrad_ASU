/*
AUTHOR: Tyler Fichiera
FILENAME: Student.java
SPECIFICATION: Class for Student object
FOR: CSE 110 Lab #7
TIME SPENT: 30 mins
*/

package Lab7;

public class Student {
    // init private vars
    private String firstName, lastName, fullName, asuID;
    private double grade = -1;

    public Student(String fname, String lname, String asuId) {
        // assign constructor args to private vars
        firstName = fname;
        lastName = lname;
        fullName = fname + " " + lname;
        asuID = asuId;
    }


    // toString method for printing out detail about the object
    public String toString() {
        return String.format(
            "First Name: %s, Last Name: %s, Full Name: %s, ASU ID: %s, Grade: %f",
            firstName, lastName, fullName, asuID, grade
        );
    }

    // getter for first name
    public String getFirstName() {
        return firstName;
    }

    // getter for last name
    public String getLastName() {
        return lastName;
    }

    // getter for full name
    public String getFullName() {
        return fullName;
    }

    // getter for asu ID
    public String getAsuID() {
        return asuID;
    }

    // getter for grade
    public double getGrade() {
        return grade;
    }

    // setter for grade
    public void setGrade(double newGrade) {
        grade = newGrade;
    }
}