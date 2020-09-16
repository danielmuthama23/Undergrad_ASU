/*
AUTHOR: Tyler Fichiera
FILENAME: Lab1.java
SPECIFICATION: Source for Lab 1
FOR: CSE 110 Lab #1
TIME SPENT: 20 mins
*/
import java.util.Scanner;

public class Lab1 
{
	public static void main(String[] args) 
	{
		double test1, test2, test3 = 0;
		final double NUM_TESTS = 3;
		
        Scanner input = new Scanner(System.in);
		
		System.out.print("Enter the score on the first test: ");
		test1 = input.nextDouble();
		
		System.out.print("Enter the score on the second test: ");
		test2 = input.nextDouble();
		
		System.out.print("Enter the score on the third test: ");
		test3 = input.nextDouble();
		
		final double avg = (test1 + test2 + test3) / NUM_TESTS;
        System.out.print("Your avg score is: " + avg);
        
        input.close();
	}
}
