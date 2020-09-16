/*
AUTHOR: Tyler Fichiera
FILENAME: Lab3.java
SPECIFICATION: Source for Lab 3
FOR: CSE 110 Lab #3
TIME SPENT: 20 mins
*/
import java.util.Scanner;

public class Lab3 {
    public static void main(String[] args) {
        // initialize scanner class
        Scanner input = new Scanner(System.in);

        // declare variables for hw, midterm and final exam grades
        int homeworkGrade = 0, midtermExamGrade = 0, finalExamGrade = 0;

        // declare a loop control variable
        int i = 0;

        // while loop for receiving valid user inputs
        while (i < 3) {
            if (i == 0) {
                // read user input for question
                System.out.print("Enter your HOMEWORK grade: ");
                homeworkGrade = input.nextInt();
            
                // check if the input is within range.
                // if not allow user to retry
                if (homeworkGrade < 0 || homeworkGrade > 100) {
                    System.out.println("Your HOMEWORK grade must be in the range [0,100]. Please try again.");
                } else {
                    i++;
                }
            } else if (i == 1) {
                System.out.print("Enter your MIDTERM EXAM grade: ");
                midtermExamGrade = input.nextInt();

                if (midtermExamGrade < 0 || midtermExamGrade > 100) {
                    System.out.println("Your MIDTERM EXAM grade must be in the range [0,100]. Please try again.");
                } else {
                    i++;
                }
            } else if (i == 2) {
                System.out.print("Enter your FINAL EXAM grade: ");
                finalExamGrade = input.nextInt();

                if (finalExamGrade < 0 || finalExamGrade > 200) {
                    System.out.println("Your FINAL EXAM grade must be in the range [0,200]. Please try again.");
                } else {
                    i++;
                }
            }
        }

        // Calculated weighted total by the formula showed in the PDF
        double weightedTotal = (homeworkGrade * .25) + (midtermExamGrade * .25) + (finalExamGrade / 200 * 50);
        
        System.out.println("[INFO] Student's Weighted Total is " + weightedTotal);

        // check if the student passed or failed the class
        if (weightedTotal >= 50) {
            System.out.println("[INFO] Student PASSED the class");
        } else {
            System.out.println("[INFO] Student FAILED the class");
        }

        input.close();
    }  // End of main
}  // End of class
