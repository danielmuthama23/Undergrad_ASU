/*
AUTHOR: Tyler Fichiera
FILENAME: Student.java
SPECIFICATION: Class for Student object
FOR: CSE 110 Lab #8
TIME SPENT: 30 mins
*/

package Lab8;

public class Student {
    // init private vars
    private String fullName, asuID;
    private double grade = -1;
    private int numOfAccessed, numOfUpdates;

    // default constructor for Student
    public Student() {}
    
    // overload constructor for Student that accepts ffullName, fasuID, fgrade
    public Student(String ffullName, String fasuID, double fgrade) {
        // set arguments as instance variables
        this.fullName = ffullName;
        this.asuID = fasuID;
        this.grade = fgrade;
    }

    // equals method for comparing the current object to another Student instance
    public boolean equals(Student other) {
        return (
            this.asuID != null && // check that current asuID is not null
            other.getAsuID() != null && // check that the other Student's asuID is not null
            this.asuID.equals(other.getAsuID()) // compare current asuID to other Student's asuID
        ) || (
            this.fullName != null && // check that current fullName is not null
            other.getFullname() != null && // check that the other Student's fullName is not null
            this.fullName.toLowerCase().equals(other.getFullname().toLowerCase()) // compare the lower case version of each fullName to eachother
        );
    }

    // toString method for printing out detail about the object
    public String toString() {
        return String.format("[Name: %s, ASUID: %s, Grade: %.2f]", this.fullName, this.asuID, this.grade);
    }

    // getter for full name
    public String getFullname() {
        // increment numOfAccessed instance variable when getter is called
        this.numOfAccessed++;
        return this.fullName;
    }

    // getter for asu ID
    public String getAsuID() {
        // increment numOfAccessed instance variable when getter is called
        this.numOfAccessed++;
        return this.asuID;
    }

    // getter for grade
    public double getGrade() {
        // increment numOfAccessed instance variable when getter is called
        this.numOfAccessed++;
        return this.grade;
    }

    // getter for numOfUpdates
    public int getNumOfUpdates() {
        // increment numOfAccessed instance variable when getter is called
        this.numOfAccessed++;
        return this.numOfUpdates;
    }

    // getter for numOfAccessed
    public int getNumOfAccessed() {
        // increment numOfAccessed instance variable when getter is called
        this.numOfAccessed++;
        return this.numOfAccessed;
    }

    // setter for asuID
    public void setId(String id) {
        // increment numOfUpdates instance variable when setter is called
        this.numOfUpdates++;
        this.asuID = id;
    }
    
    // setter for fullName
    public void setName(String newName) {
        // increment numOfUpdates instance variable when setter is called
        this.numOfUpdates++;
        this.fullName = newName;
    }
    
    // setter for grade
    public void setGrade(double newGrade) {
        // increment numOfUpdates instance variable when setter is called
        this.numOfUpdates++;
        this.grade = newGrade;
    }
}