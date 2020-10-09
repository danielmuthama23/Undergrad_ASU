/*
AUTHOR: Tyler Fichiera
FILENAME: Lab6.java
SPECIFICATION: Source for Lab 6
FOR: CSE 110 Lab #6
TIME SPENT: 20 mins
*/
import java.util.Scanner;

public class Lab6 {
    public static void main(String[] args) {
        // initialize Scanner object
        Scanner input = new Scanner(System.in);

        // input for number of students
        System.out.println("How many students do you have? ");
        int numStudents = input.nextInt();
        
        // initialize arrays by numStudents
        int[] studentGroups = new int[numStudents];
        double[] studentGrades = new double[numStudents];

        int numGroups = -1;

        // input for each student, group # and grade
        for (int i = 0; i < numStudents; i++) {
            System.out.println("[Group #] and [Grade] for Entry " + (i + 1));
            studentGroups[i] = input.nextInt();
            studentGrades[i] = input.nextDouble();
        }

        // Display student records
        System.out.println("\n==== List of Student Records =====");
        for (int i = 0; i < numStudents; i++) {
            System.out.println("Group " + studentGroups[i] + " - " + studentGrades[i] + " Points");

            // find the number of groups
            if (studentGroups[i] > numGroups) {
                numGroups = studentGroups[i];
            }
        }

        // init arrays based off number of groups
        // + 1 to avoid group 0
        int[] groupSizes = new int[numGroups + 1];
        double[] groupGradeSums = new double[numGroups + 1];

        // calculate stats for each student
        for (int i = 0; i < numStudents; i++) {
            int studentGroup = studentGroups[i];
            groupSizes[studentGroup]++;
            groupGradeSums[studentGroup] += studentGrades[i];
        }
        
        // calculate average + display statistics for each group
        System.out.println("\n==== Group Statistics =====");
        for (int i = 1; i < numGroups + 1; i++) {
            double average = groupGradeSums[i] / groupSizes[i];
            System.out.printf("Group #" + i + " has " + groupSizes[i] + " students, average is %.2f\n", average);
        }

        input.close();
    }
}
