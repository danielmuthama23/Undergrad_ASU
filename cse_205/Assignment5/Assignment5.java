// Assignment #: 5
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: The Assignment 5 class displays a menu of choices to a user
//               and performs the chosen task. It will keep asking a user to
//               enter the next choice until the choice of 'Q' (Quit) is
//               entered.

import java.io.*;   // to use InputStreamReader and BufferedReader
import java.util.*; // to use ArrayList

public class Assignment5 {
    public static void main (String[] args) {
        // init vars for inputs
        char input1;
        String inputInfo = new String();
        String line = new String();

        // ArrayList object is used to store student objects
        ArrayList<Student> studentList = new ArrayList<Student>();

        try {
            printMenu(); // print out menu

            // create a BufferedReader object to read input from a keyboard
            InputStreamReader isr = new InputStreamReader(System.in);
            BufferedReader stdin = new BufferedReader(isr);

            do {
                // prompt user
                System.out.println("What action would you like to perform?");
                line = stdin.readLine().trim();
                input1 = line.charAt(0);
                input1 = Character.toUpperCase(input1);

                if (line.length() == 1) {
                    // switch statement for inputs
                    switch (input1) {
                        case 'A':   // Add Student
                            System.out.print("Please enter a student information to add:\n");
                            inputInfo = stdin.readLine().trim();
                            // call helper class to parse input
                            Student student = StuParser.parseStringToStudent(inputInfo);
                            studentList.add(student); // add to arraylist
                            break;
                        case 'C':   // Compute tuition
                            for (Student stu : studentList)
                                stu.computeTuition();
                            System.out.print("tuition computed\n");
                            break;
                        case 'D':   // Count certain students
                            System.out.print("Please enter a number of credits:\n");
                            inputInfo = stdin.readLine().trim();
                            int credits = Integer.parseInt(inputInfo);
                            int count = 0;
                            for (Student stu : studentList) {
                                if (stu.getNumCredit() == credits) count++; // increase count when credits match
                            }                        
                            System.out.println(
                                "The number of students who are taking " + credits + " credits is: " + count
                            ); 
                            break;
                        case 'L':   // List Students
                            if (studentList.size() == 0) {
                                System.out.print("no student\n");
                            } else {
                                for (Student stu : studentList)
                                    System.out.println(stu); // call toString of student
                            }
                            break;
                        case 'Q':   // Quit
                            break;
                        case '?':   // Display Menu
                            printMenu();
                            break;
                        default:
                            System.out.print("Unknown action\n");
                            break;
                    }
                } else {
                    System.out.print("Unknown action\n");
                }
            } while (input1 != 'Q'); // stop the loop when Q is read
        } catch (IOException exception) {
            System.out.println("IO Exception");
        }
    }

    /** The method printMenu displays the menu to a user */
    public static void printMenu() {
        System.out.print(
            "Choice\t\tAction\n" +
            "------\t\t------\n" +
            "A\t\tAdd Student\n" +
            "C\t\tCompute Tuition\n" +
            "D\t\tCount Certain Students\n" +
            "L\t\tList Students\n" +
            "Q\t\tQuit\n" +
            "?\t\tDisplay Help\n\n"
        );
    }
}