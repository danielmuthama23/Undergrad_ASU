/*
AUTHOR: Tyler Fichiera
FILENAME: Lab7.java
SPECIFICATION: Test Driver for Lab 7
FOR: CSE 110 Lab #7
TIME SPENT: 30 mins
*/

package Lab7;

import java.util.Scanner;

public class Lab7 {
    public static void main(String[] args) {
        // init scanner
        Scanner scan = new Scanner(System.in);

        // Read some input data
        print("The student's first name? ");
        String sFirstname = scan.nextLine();
        print("The student's last name? ");
        String sLastname = scan.nextLine();
        print("The student's ASU ID? ");
        String sAsuID = scan.nextLine();
        print("Program name? ");
        String pName = scan.nextLine();
        print("Program desc? ");
        String pDesc = scan.nextLine();
        print("Program filename? ");
        String pFname = scan.nextLine();
        print("Program grade? ");
        double sGrade = scan.nextDouble();
        println("");
        scan.close(); // close the scanner object

        // Create a Student object "student1"
        Student student1 = new Student(sFirstname, sLastname, sAsuID);
        System.out.println("Making a student record\n...[" + student1 + "]");

        // Use the setGrade setter to set student1's grade
        student1.setGrade(sGrade); // set user's grade

        // Create a Program object "program1" by "student1"
        Program program1 = new Program(pName, pDesc, pFname, student1);
        System.out.println("Making a program record\n...[" + program1 + "]");

        // Invoke makeReport to show the report of student1
        makeReport(program1);
    }

    // helper method to display detail about the program
    private static void makeReport(Program program) {
        // print out detail about the program
        println("\n========== Program Submission Detail ==========");
        pprint("Student", program.getAuthor().getFullName());
        pprint("ASU ID", program.getAuthor().getAsuID());
        pprint("Grade", "" + program.getAuthor().getGrade());
        println("");
        pprint("Program", program.getProgramName());
        pprint("Filename", program.getFileName());
        pprint("Description", program.getDescription());
        pprint("Datetime", program.getCreatedDate());
    }

    // helper method for pretty print
    private static void pprint(String key, String value) {
        println(String.format("%-12s: %-10s", key, value));
    }

    // helper method for normal print
    private static void print(String s) {
        System.out.print(s);
    }

    // helper method for line print
    private static void println(String s) {
        System.out.println(s);
    }
}