// Assignment #: 5
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: Abstract class that is implemented by Graduate.java
//               and UnderGrad.java

import java.text.DecimalFormat;

public abstract class Student {
    protected String firstName;
    protected String lastName;
    protected String studentID;
    protected int numCredits;
    protected double rate;
    protected double tuition;
    
    public Student(String fName, String lName, String id, int credits, double rate) {
        // populate protected instance vars
        this.firstName = fName;
        this.lastName = lName;
        this.studentID = id;
        this.numCredits = credits;
        this.rate = rate;
        this.tuition = 0.0;
    }

    /** getter for numCredits */
    public int getNumCredit() {
        return this.numCredits;
    }

    /** helper method that must be implemented by children */
    public abstract void computeTuition();

    /** prints useful info about the Student */
    public String toString() {
        DecimalFormat money = new DecimalFormat("$##,##0.00");
        return String.format(
            "\nFirst name:\t\t%s\nLast name:\t\t%s\n" +
            "Student ID:\t\t%s\nCredits:\t\t%d\nRate:\t\t\t%s\n" +
            "Tuition:\t\t%s\n",
            this.firstName,
            this.lastName,
            this.studentID,
            this.numCredits,
            money.format(this.rate),
            money.format(this.tuition)
        );
    }
}