// Assignment #: 5
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: Class for Graduate student that extends the abstract
//               class Student

import java.text.DecimalFormat;

public class Graduate extends Student {
    // init private instance vars
    private double gradFee;

    /** constructor that calls parent's constructor using super() */
    public Graduate(String fName, String lName, String id, int credits, double rate, double gradFee) {
        // call super and populate instance variables
        super(fName, lName, id, credits, rate);
        this.gradFee = gradFee;
    }

    /** calculates tuition use private and protected instance vars */
    public void computeTuition() {
        this.tuition = this.rate * this.numCredits + this.gradFee;
    }

    /** method override for toString, prints useful info about Grad student */
    @Override
    public String toString() {
        // init money formatter
        DecimalFormat money = new DecimalFormat("$##,##0.00");
        return String.format(
            "\nGraduate Student:\nFirst name:\t\t%s\nLast name:\t\t%s\n" +
            "Student ID:\t\t%s\nCredits:\t\t%d\nRate:\t\t\t%s\n" +
            "Tuition:\t\t%s\nGrad Fee:\t\t%s\n",
            this.firstName,
            this.lastName,
            this.studentID,
            this.numCredits,
            money.format(this.rate),
            money.format(this.tuition),
            money.format(this.gradFee)
        );
    }
}