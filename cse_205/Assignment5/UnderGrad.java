// Assignment #: 5
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: Class for Graduate student that extends the abstract
//               class Student

import java.text.DecimalFormat;

public class UnderGrad extends Student {
    private boolean inState;
    private int creditUpperbound;
    private double programFee;

    /** constructor that calls parent's constructor using super() */
    public UnderGrad(
        String fName,
        String lName,
        String id,
        int credits,
        double rate,
        boolean inState,
        double programFee
    ) {
        // call super and populate instance variables
        super(fName, lName, id, credits, rate);
        this.inState = inState;
        this.creditUpperbound = inState == true ? 7 : 12;
        this.programFee = programFee;
    }

    /** calculates tuition based on number of credits */
    public void computeTuition() {
        this.tuition = this.numCredits >= this.creditUpperbound
            ? this.rate * this.creditUpperbound + this.programFee
            : this.rate * this.numCredits + this.programFee;
    }

    /** method override for toString, prints useful info about student */
    @Override
    public String toString() {
        DecimalFormat money = new DecimalFormat("$##,##0.00");
        return String.format(
            "\nUnderGrad:\n%s\nFirst name:\t\t%s\n" +
            "Last name:\t\t%s\nStudent ID:\t\t%s\nCredits:\t\t%d\n" +
            "Rate:\t\t\t%s\nTuition:\t\t%s\nStudent Program Fee:\t%s\n",
            this.inState == true ? "In-State" : "Out-Of-State",
            this.firstName,
            this.lastName,
            this.studentID,
            this.numCredits,
            money.format(this.rate),
            money.format(this.tuition),
            money.format(this.programFee)
        );
    }
}