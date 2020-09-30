/*
AUTHOR: Tyler Fichiera
FILENAME: Lab5.java
SPECIFICATION: Source for Lab 5
FOR: CSE 110 Lab #5
TIME SPENT: 20 mins
*/
import java.util.Scanner;

public class Lab5 {
    public static void main(String[] args) {
        // declare consts
        final char SIDE_SYMB = '-';
        final char MID_SYMB = '*';

        // init Scanner
        Scanner input = new Scanner(System.in);
        
        // init vars
        String inputStr = "";
        char menuSelection = ' ';
        int numSymbols, sideWidth, midWidth;

        do {
            // display the menu
            displayMenu();

            // ask the user for one option
            System.out.print("Your selection: ");
            inputStr = input.nextLine();

            // prevent exception for empty lines
            if (inputStr.length() > 0) {
                menuSelection = inputStr.charAt(0);
            } else {
                menuSelection = ' ';
            }
            
            // switch statement to handle user selections
            switch (menuSelection) {
                case 'r':
                    System.out.print("Width of the sides: ");
                    sideWidth = input.nextInt();

                    System.out.print("Width of the middle: ");
                    midWidth = input.nextInt();

                    System.out.println();
                    System.out.println(buildRow(SIDE_SYMB, sideWidth, MID_SYMB, midWidth));

                    input.nextLine();  // Flush junk newline symbols
                    break;
                case 'p':
                    System.out.print("Number of symbols on the lowest layer: ");
                    numSymbols = input.nextInt(); 

                    System.out.println();
                    System.out.print(buildPyramid(SIDE_SYMB, MID_SYMB, numSymbols));

                    input.nextLine();  // Flush junk newline symbols
                    break;
                case 'd':
                    System.out.print("Number of symbols on the middle layer: ");
                    numSymbols = input.nextInt();

                    System.out.println();
                    System.out.print(buildDiamond('*', ' ', numSymbols));

                    input.nextLine();  // Flush junk newline symbols
                    break;
                case 'q':
                    System.out.println("Bye!");
                    break;
                default:
                    System.out.println("Please enter a valid selection from the display menu!");
                    break;
            }

            System.out.println();
        } while (menuSelection != 'q');
        
        input.close();
    }

    /**
     * Build a row of symbols (pattern) with the given parameters. 
     *
     * For example, -----*****----- can be built by the parameters
     *
     * sideWidth = 5, midWidth = 5, sideSymb = '-', midSymb = '*'
     * 
     * @param sideSymb  A char to be repeated on both sides
     * @param sideWidth Number of symbols on each side
     * @param midSymb   A char to be repeated in the middle
     * @param midWidth  Number of symbols in the middle
     * @return          A String of a row of the designed pattern
     */
    private static String buildRow(char sideSymb, int sideWidth, char midSymb, int midWidth) {
        String result = "";
        
        for (int i = 0; i < sideWidth; i++) {
            result += sideSymb;
        }
        for (int i = 0; i < midWidth; i++) {
            result += midSymb;
        }
        for (int i = 0; i < sideWidth; i++) {
            result += sideSymb;
        }

        return result;
    }

    /**
     * Build a pyramid pattern with the given parameters.
     *
     * For example, the following pattern
     *
     *  -----*-----
     *  ----***----
     *  ---*****---
     *  --*******--
     *  -*********-
     *  ***********
     *
     * can be built by sideSymb = '-', midSymb = '*', numSymbols = 11
     *
     * When ptnHeight is not an odd integer, replace it by the closest
     * even integer below. For example, if numSymbols is 10, use 9 instead.
     * 
     * When ptnHeight is 0, return an empty String.
     * 
     * @param  sideSymb   A char to be repeated on both sides
     * @param  midSymb    A char to be repeated in the middle
     * @param  numSymbols The number of symbols on the lowest layer
     * @return            A String of the pyramid pattern.
     */
    private static String buildPyramid(char sideSymb, char midSymb, int numSymbols) {
        String result = "";

        int totalSymbOneRow = numSymbols;

        for (int numStars = 1; numStars <= numSymbols; numStars += 2) {
            int numDashed = (totalSymbOneRow - numStars) / 2;
            String row = buildRow(sideSymb, numDashed, midSymb, numStars);
            result += row + "\n";
        }

        return result;
    }

    /**
     * Build a diamond pattern. The parameters are the same 
     * as {@link #buildPyramid(char, char, int)}.
     * 
     * @param  sideSymb  A char to be repeated on both sides
     * @param  midSymb   A char to be repeated in the middle
     * @param  numSymbols The height of a pyramid
     * @return           A String of the inverted diamond pattern.
     */
    private static String buildDiamond(char sideSymb, char midSymb, int numSymbols) {
        String result = "";

        int totalSymbOneRow = numSymbols;
        
        for (int numStars = 1; numStars <= numSymbols; numStars += 2) {
            int numSideChars = (totalSymbOneRow - numStars) / 2; 
            String row = buildRow(sideSymb, numSideChars, midSymb, numStars);
            result += row + "\n";
        }
        for (int numStars = numSymbols; numStars >= 1; numStars -= 2) {
            int numSideChars = (totalSymbOneRow - numStars) / 2;
            if (numSideChars > 0) {
                String row = buildRow(sideSymb, numSideChars, midSymb, numStars);
                result += row + "\n";
            }
        }
         
        return result;
    }
    
    /**
     * Display the menu
     */
    private static void displayMenu() {
        System.out.println("Please choose one pattern from the list");
        System.out.println("r) Row");
        System.out.println("p) Pyramid");
        System.out.println("d) Shallow diamond");
        System.out.println("q) Quit");
    }

}
