/*
CSE 110
Assignment: Assignment 02
Author: Tyler Fichiera 1218959911
Description: Source for assignment 2
*/
import java.util.Scanner;

public class Assignment02 {
    public static void main(String[] args) {
        // declare and instantiate a Scanner
        Scanner input = new Scanner(System.in);

        // declare and initialize variables
        double roadLength;
        int numLanes, asphaltDepth, daysToComplete;
        
        // collect inputs
        System.out.print("Length of road (miles)  : ");
        roadLength = input.nextDouble();

        System.out.print("Number of lanes         : ");
        numLanes = input.nextInt();       

        System.out.print("Depth of asphalt        : ");
        asphaltDepth = input.nextInt();

        System.out.print("Days to complete        : ");
        daysToComplete = input.nextInt();

        // store feet to mile conversion as const
        final int FEET_IN_ONE_MILE = 5280;

        // compute amount of materials
        double asphaltVolume = (numLanes * 12) * (roadLength * FEET_IN_ONE_MILE) * (asphaltDepth / 12.0); // in cubic ft
        double asphaltWeight = (asphaltVolume * 150) / 2000; // in tons
        int truckloads = (int)Math.ceil(asphaltWeight / 5);

        int stoplights = (int)roadLength * (2 + numLanes);

        int conduitPipes = (int)Math.ceil(roadLength * FEET_IN_ONE_MILE / 24);

        int crewMembersNeeded = (int)Math.ceil((50 * roadLength * numLanes) / daysToComplete);

        // compute cost of materials
        double asphaltCost = truckloads * 1000;

        double stoplightsCost = stoplights * 25000;

        double pipesCost = Math.ceil(roadLength * FEET_IN_ONE_MILE / 24) * 500;

        double laborCost = crewMembersNeeded * 25 * 8 * daysToComplete;

        double totalCost = asphaltCost + stoplightsCost + pipesCost + laborCost;
        
        // display results
        System.out.println("=== Amount of materials needed ===");
        System.out.println("Truckloads of asphalt   : " + truckloads);
        System.out.println("Stoplights              : " + stoplights);
        System.out.println("Conduit pipes           : " + conduitPipes);
        System.out.println("Crew members needed     : " + crewMembersNeeded);
        System.out.println("=== Cost of Materials ============");
        System.out.printf("Cost of asphalt         : $%.2f\n", asphaltCost);
        System.out.printf("Cost of stoplights      : $%.2f\n", stoplightsCost);
        System.out.printf("Cost of conduit pipes   : $%.2f\n", pipesCost);
        System.out.printf("Cost of labor           : $%.2f\n", laborCost);
        System.out.println("=== Total Cost of Project ========");
        System.out.printf("Total cost of project   : $%.2f\n", totalCost);
         
        input.close();
    }

}
