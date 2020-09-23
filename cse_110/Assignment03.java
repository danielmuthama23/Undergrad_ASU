/*
CSE 110 83315 / T 1:30-2:20 PM
Assignment: Assignment 03
Author: Tyler Fichiera 1218959911
Description: Source for assignment 3
*/
import java.util.Scanner;

public class Assignment03 {
    public static void main(String[] args) {
        // Declare and instantiate a Scanner
        Scanner input = new Scanner(System.in);

        System.out.print("Current Shares  : ");
        int currentShares = input.nextInt();

        System.out.print("Purchase Price  : ");
        int purchasePrice = input.nextInt();

        System.out.print("Market Price    : ");
        int marketPrice = input.nextInt();

        System.out.print("Available Funds : ");
        int availableFunds = input.nextInt();

        // Calculate Total Buy Value
        int perShareBuyValue = purchasePrice - marketPrice;

        int numberOfSharesToBuy = (availableFunds - 10) / marketPrice;

        int totalBuyValue = perShareBuyValue * numberOfSharesToBuy;
        
        // Calculate Total Sell Value
        int perShareSellValue = marketPrice - purchasePrice;
        
        int totalSellValue = perShareSellValue * currentShares;

        // Logic for determining whether to Buy, Sell, or Hold
        if (totalBuyValue > 10 || totalSellValue > 10) {
            if (totalBuyValue > totalSellValue) {
                System.out.println("Buy " + numberOfSharesToBuy + " shares");
            } else if (totalBuyValue < totalSellValue) {
                System.out.println("Sell " + currentShares + " shares");
            } else {
                System.out.println("Buy " + numberOfSharesToBuy + " shares or sell " + currentShares + " shares");
            }
        } else {
            System.out.println("Hold Shares");
        }

        input.close();
    }
}
