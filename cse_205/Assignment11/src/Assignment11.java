// Assignment #: 11
// Name: Tyler Fichiera
// StudentID: 1218959911
// Lecture: T/Th 4:30
// Section: 33116
// Description: Assignment 10 class displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.

import java.io.*;

public class Assignment11
 {
  public static void main (String[] args) throws IOException
   {
       char input1;
       String inputInfo = new String();
       String line = new String();
       int queenNum;

       printMenu();

       InputStreamReader isr = new InputStreamReader(System.in);
       BufferedReader stdin = new BufferedReader(isr);

       do  // will ask for user input
        {
         System.out.println("What action would you like to perform?");
         line = stdin.readLine();
         input1 = line.charAt(0);
         input1 = Character.toUpperCase(input1);

         if (line.length() == 1)
          {
           // matches one of the case statements
           switch (input1)
            {
             case 'E':   //Enter Problem parameter
               System.out.print("Please enter a number of queens.\n");
               inputInfo = stdin.readLine().trim();
               queenNum = Integer.parseInt(inputInfo);

               //Create a solver for this problem.
               NQueenSolver solver = new NQueenSolver(queenNum);
               boolean found = solver.findSolution();

               if (found == true)
                 {
                  Answer answer1 = solver.returnAnswer();
                  System.out.print("solution found\n");
                  System.out.print(answer1.toString());
                 }
               else
                 System.out.print("solution not found\n");
               break;
             case 'Q':   //Quit
               break;
             case '?':   //Display Menu
               printMenu();
               break;
             default:
               System.out.print("Unknown action\n");
               break;
            }
          }
         else
          {
           System.out.print("Unknown action\n");
          }
        } while (input1 != 'Q' || line.length() != 1);
   }


  /** The method printMenu displays the menu to a user**/
  public static void printMenu()
   {
     System.out.print("Choice\t\tAction\n" +
                        "------\t\t------\n" +
                        "E\t\tEnter Problem Parameter\n" +
                        "Q\t\tQuit\n" +
                        "?\t\tDisplay Help\n\n");
  }
}
