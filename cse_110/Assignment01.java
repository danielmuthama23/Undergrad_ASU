/*
CSE 110
Assignment: Assignment 01
Author: Tyler Fichiera 1218959911
Description: Source for assignment 1
*/
import java.util.Scanner;

public class Assignment01 {
    public static void main(String[] args) {  
        // declare and instantiate a Scanner
        Scanner input = new Scanner(System.in);

        // declare and initialize variables
        int pizzasPurchased, slicesPerPizza, numAdults, numChildren;       
        
        // prompt for and collect inputs
        System.out.print("Number of pizzas purchased: ");
        pizzasPurchased = input.nextInt();
        
        System.out.print("Number of slices per pizza: ");
        slicesPerPizza = input.nextInt();
        
        System.out.print("Number of adults: ");
        numAdults = input.nextInt();
        
        System.out.print("Number of children: ");
        numChildren = input.nextInt();

        // compute required values
        final int totalSlices = pizzasPurchased * slicesPerPizza;
        final int totalAdultSlices = 2 * numAdults;
        final int totalChildSlices = totalSlices - totalAdultSlices;
        final int slicesPerChild = totalChildSlices / numChildren;
        final int slicesLeftOver = totalChildSlices % numChildren;

        // display required outputs
        System.out.println("Total number of slices of pizza                 : " + totalSlices);
        System.out.println("Total number of slices given to adults          : " + totalAdultSlices);
        System.out.println("Total number of slices available for children   : " + totalChildSlices);
        System.out.println("Number of slices each child will get            : " + slicesPerChild);
        System.out.println("Number of slices left over                      : " + slicesLeftOver);

        input.close();
    }
}
