// Assignment #: 1
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th - 4:30
//  Description: This class reads an integer from a keyboard and prints it out
//               along with other messages.

import java.util.Scanner;  // use the Scanner class located in the "java.util" directory

public class Assignment1 {
    public static void main (String[] args) {
        // init Scanner object
        Scanner input = new Scanner(System.in);

        // read an integer entered by a user
        int number = input.nextInt();

        // display the number with other messages
        System.out.print(
            "This program reads an integer from a keyboard,\n"
            + "and prints it out on the display screen.\n"
            + "The number is:" + number + "\n"
            + "Make sure that you get the exact same output as the expected one!\n"
        );
    }
}


