// Assignment #: 2
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th - 4:30
//  Description: This class reads a sequence of integers and calculates some
//               info and prints it out
package Assignment2;

import java.util.Scanner;  // use the Scanner class located in the "java.util" directory

public class Assignment2 {
    public static void main(String[] args) {
        // init Scanner object
        Scanner input = new Scanner(System.in);

        // declare info vars
        int inputNum,
            maxInt = 0,
            numEvenInts = 0,
            smallestOddInt = 0,
            sumNegInts = 0;

        do {
            // read an integer entered by a user
            inputNum = input.nextInt();

            // replace maxInt var if input larger
            if (maxInt == 0 || inputNum > maxInt) {
                maxInt = inputNum;
            }

            // check if input is even
            if (inputNum % 2 == 0) {
                numEvenInts++; // if even, increase even counter
            } else if (smallestOddInt == 0 || inputNum < smallestOddInt) {
                // input is odd at this point
                // replace smallestOddInt var if input smaller
                smallestOddInt = inputNum;
            }

            // check if input is negative
            if (inputNum < 0) {
                sumNegInts += inputNum; // add input to negative num sum
            }
        } while (inputNum != 0); // stop loop, but include inputted zero

        // print out the calculated results
        System.out.print(
            "The maximum integer is " + maxInt + "\n"
            + "The count of even integers in the sequence is " + numEvenInts + "\n"
            + "The smallest odd integer in the sequence is " + smallestOddInt + "\n"
            + "The sum of negative integers is " + sumNegInts + "\n"
        );

        // close scanner object as best practice
        input.close();
    }
}