/*
AUTHOR: Tyler Fichiera
FILENAME: Lab4.java
SPECIFICATION: Source for Lab 4
FOR: CSE 110 Lab #4
TIME SPENT: 15 mins
*/
import java.util.Scanner;

public class Lab4 {
    public static void main(String[] args) {
        // initialize scanner and menu selection variable
        Scanner input = new Scanner(System.in);
        int menuSelection;

        do {
            // display the menu
            displayMenu();

            // ask the user for one option
            System.out.print("Your selection: ");
            menuSelection = input.nextInt();
            
            // switch statement to handle user selections
            switch (menuSelection) {
                case 1:
                    System.out.print("Enter a number: ");
                    int num1 = input.nextInt();
                    System.out.println("The sum of 1 to " + num1 + " is " + calculateSummation(num1));
                    break;
                case 2:
                    System.out.print("Enter a number: ");
                    int num2 = input.nextInt();
                    System.out.println("The factorial of " + num2 + " is " + calculateFactorial(num2));
                    break;
                case 3:    
                    System.out.print("Enter a number: ");
                    int num3 = input.nextInt();
                    System.out.println("The leftmost digit of " + num3 + " is " + leftmostDigit(num3));
                    break;
                case 4:
                    System.out.println("Bye!");
                    break;
                default:
                    System.out.println("Please enter a valid selection from the display menu!");
                    break;
            }

            System.out.println();
        } while (menuSelection != 4);

        input.close();
    }

    /**
     * Display the options menu on the console
    */
    private static void displayMenu() {
        System.out.println("Please choose one option from the following menu:");
        System.out.println("1) Calculate the sum of integers from 1 to m");
        System.out.println("2) Calculate the factorial of a given number");
        System.out.println("3) Display the leftmost digit of a given number");
        System.out.println("4) Quit");
    }

    /**
     * Calculates the summation of a given integer
     * @param num the base integer of the summation
     * @return the summation of num
    */
    private static int calculateSummation(int num) {
        int sum = 0;
        for (int i = 1; i < num + 1; i++) {
            sum += i;
        }
        return sum;
    }    

    /**
     * Calculates the factorial of a given integer
     * @param num the base integer of the factorial
     * @return the factorial of num
    */
    private static int calculateFactorial(int num) {
        int factorial = 1;
        for (int i = 2; i < num + 1; i++) {
            factorial *= i;
        }
        return factorial;
    }


    /**
     * Finds the leftmost digit of a given integer
     * @param num the base integer
     * @return the leftmost digit of num
    */
    private static int leftmostDigit(int num) {
        while (num >= 10) {
            num /= 10;
        }
        return num;
    }
}