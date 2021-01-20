/*
Assignment #: 4
Arizona State University - CSE205
Name: Tyler Fichiera
StudentID: 1218959911
Lecture: T/Th - 4:30
Description: Assignment 4 class displays a menu of choices to a user
    and performs the chosen task. It will keep asking a user to
    enter the next choice until the choice of 'Q' (Quit) is entered.
*/
package Assignment4;

import java.util.*;

public class Assignment4
 {
  public static void main (String[] args)
   {
       // local variables, can be accessed anywhere from the main method
       char input1 = 'Z';
       //String inputInfo= "";
       String depName, university, firstName, lastName, academicLevel, numOfMembersStr;
       int numOfMembers;
       String line = new String();

       // instantiate a Department object
       Department depar1 = new Department();

       printMenu();

       //Create a Scanner object to read user input
       Scanner scan = new Scanner(System.in);

       do  // will ask for user input
        {
            System.out.println("What action would you like to perform?");
            line = scan.nextLine();
            
            if (line.length() == 1)
            {
                input1 = line.charAt(0);
                input1 = Character.toUpperCase(input1);

                // matches one of the case statement
                switch (input1)
                {
                    case 'A':   //Add Department
                        System.out.print("Please enter the Department information:\n");
                        System.out.print("Enter its name:\n");
                        depName = scan.nextLine();
                        depar1.setDeptName(depName);

                        System.out.print("Enter its number of members:\n");
                        numOfMembersStr = scan.nextLine();
                        numOfMembers = Integer.parseInt(numOfMembersStr);
                        depar1.setNumberOfMembers(numOfMembers);
                    
                        System.out.print("Enter its university:\n");
                        university = scan.nextLine();
                        depar1.setUniversity(university);
                        
                        System.out.print("Enter its faculty's first name:\n");
                        firstName = scan.nextLine();
                        System.out.print("Enter its faculty's last name:\n");
                        lastName = scan.nextLine();
                        System.out.print("Enter its faculty's academic level:\n");
                        academicLevel = scan.nextLine();
                        depar1.setCurrentFaculty(firstName, lastName, academicLevel);
                        break;
                    case 'D':   //Display Department
                        System.out.print(depar1.toString());
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
       scan.close();
   }

  /** The method printMenu displays the menu to a user **/
  public static void printMenu()
   {
     System.out.print("Choice\t\tAction\n" +
                        "------\t\t------\n" +
                        "A\t\tAdd Department\n" +
                        "D\t\tDisplay Department\n" +
                        "Q\t\tQuit\n" +
                        "?\t\tDisplay Help\n\n");
  }
 
}
