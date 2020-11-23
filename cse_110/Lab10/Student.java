/*
AUTHOR: Tyler Fichiera
FILENAME: Student.java
SPECIFICATION: Class for Student object
FOR: CSE 110 Lab #10
TIME SPENT: 30 mins
*/

package Lab10;

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

    // equals method for comparing the current object to another object
    public boolean equals(Object obj) {
        if (obj == null) return false; // check to make sure obj is not null
        if (!obj.getClass().equals(this.getClass())) return false; // check to make sure classes are the same
        if (((Student)obj).getId().equals(this.getId())) return true; // compare objects using custom equals method
        return false;
    }

    // toString method for printing out detail about the object
    public String toString() {
        return String.format("%18s  %s", this.fullName, this.asuID);
    }

    // getter for full name
    public String getFullName() {
        // increment numOfAccessed instance variable when getter is called
        this.numOfAccessed++;
        return this.fullName;
    }

    // getter for asu ID
    public String getId() {
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
