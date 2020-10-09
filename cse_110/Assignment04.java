/*
CSE 110 83315 / T 1:30-2:20 PM
Assignment: Assignment 04
Author: Tyler Fichiera 1218959911
Description: Source for assignment 4
*/
import java.util.Scanner;

public class Assignment04 {
    public static void main(String[] args) {
        // Declare and instantiate a Scanner
        Scanner input = new Scanner(System.in);

        boolean isPlaying = true;
        
        System.out.println("----- MASTERMIND -----");
        System.out.println("Guess the 4 digit number!");
        
        do {
            // generate secret number
            int secretNumber = genSecretNumber(0, 9999);

            // init game variables
            boolean isCorrect = false;
            int guesses = 1;

            do {
                // read guess
                System.out.print("\nGuess " + guesses + ": ");
                int currentGuess = input.nextInt();

                // get number of matched digits
                int matchedDigits = getNumberOfMatchedDigits(secretNumber, currentGuess);

                System.out.println("You matched " + matchedDigits);

                // must match all 4 digits for it to be correct
                isCorrect = matchedDigits == 4;

                if (isCorrect) {          
                    // ask user if they want to play again          
                    System.out.println("\nCongratulations! You guessed the right number in " + guesses + " guesses.");
                    System.out.print("Would you like to play again (yes/no)? ");

                    input.nextLine(); // Flush junk newline symbols
                    String playAgain = input.nextLine();

                    isPlaying = playAgain.toLowerCase().equals("yes");

                    if (isPlaying) {
                        // reset variables to start of game state
                        guesses = 1;
                        isCorrect = false;
                    } else {
                        System.out.println("\nBye!");
                    }
                } else {
                    guesses++;
                }
            } while (!isCorrect);
        } while (isPlaying); // play until the user says "no"

        input.close(); // close scanner
    }

    /**
     * Generates a random number within a given range (inclusive)
     * @param min interval minimum
     * @param max interval maximum
     * @return random integer on the inclusice interval [min, max]
    */
    private static int genSecretNumber(int min, int max) {
        return min + (int)(Math.random() * ((max - min) + 1)); 
    }

    /**
     * Get the number of matched digits between two integers
     * 
     * @param num1 first four-digit int
     * @param num2 second four-digit int
     * @return number of matched digits
    */
    private static int getNumberOfMatchedDigits(int num1, int num2) {
        // adding 10,000 guarantees that there are 5 digits to compare
        // this gives us a number that is 1XXXX
        // we subtract 1 at the end because the 1s in 1XXXX always match
        num1 += 10000;
        num2 += 10000;

        int matchedDigits = 0;
        while (num1 > 0 && num2 > 0) {
            if (num1 % 10 == num2 % 10) matchedDigits++;
            num1 /= 10;
            num2 /= 10;
        }

        return matchedDigits - 1;
    }
}
