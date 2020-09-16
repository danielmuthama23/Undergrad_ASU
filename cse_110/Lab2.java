/*
AUTHOR: Tyler Fichiera
FILENAME: Lab2.java
SPECIFICATION: Source for Lab 2
FOR: CSE 110 Lab #2
TIME SPENT: 20 mins
*/
import java.util.Scanner;

public class Lab2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        String firstName = "";
        String lastName = "";
        String fullName = "";
        int nameLength;

        System.out.print("Please enter first name: ");
        firstName = input.nextLine();

        System.out.print("Please enter last name: ");
        lastName = input.nextLine();

        fullName = firstName + ' ' + lastName;
        System.out.println("Full name (in capitals): " + fullName.toUpperCase());
        
        nameLength = fullName.length();
        System.out.println("Length of full name: " + nameLength);

        String title1 = new String("cse110");
        String title2 = "cse110"; 

        if (title1 == title2) {
            System.out.println("String comparison using \"==\" sign works");
        } else {
            System.out.println("String comparison using \"==\" sign does NOT work" );
        }

        if (title1.equals((title2))) {
            System.out.println("String comparison using \"equals\" method works");
        } else {
            System.out.println("String comparison using \"equals\" method does NOT work");
        }

        input.close();
    }
}