/*
AUTHOR: Tyler Fichiera
FILENAME: Lab85.java
SPECIFICATION: Source for Lab 8.5
FOR: CSE 110 Lab #8.5
TIME SPENT: 30 mins
*/

import java.time.LocalDate;
import java.util.Scanner;

public class Lab85 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        // Ask the user for month/year
        System.out.println("Which month/year would you like to look up the calendar?\n(ex. 11 2020)");
        int month = scan.nextInt(), day = 1, year = scan.nextInt();

        // Get the weekday and # of months of the given month/year
        int numOfDays = getNumOfDays(month, year);
        int weekDay = getWeekDayOf(month, day, year);

        // Create a 2D array with enough space for at least 30 days
        String[][] calendar = new String[5][7];

        /*
         * Fill in the 2D array by the calendar in November 2020 You need to align
         * weekdays with indices in your 2D array. The first index of a row of week is
         * Sunday and the last is Saturday.
         */
        int totalDays = 1, countedDays = 1; // init two variables, one for all days, one for counted days
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 7; c++) {
                if (totalDays < weekDay || countedDays > numOfDays) {
                    // fill leading and trailing elements with "-"
                    calendar[r][c] = "-";
                } else {
                    // fill valid indexes with the correct day number
                    calendar[r][c] = Integer.toString(countedDays);
                    countedDays++; // increment only on valid days
                }
                totalDays++; // increment over every index in the array
            }
        }

        // Print out the calendar
        System.out.println();
        System.out.printf("     The Calendar for %2d/%4d\n", month, year);
        System.out.printf("-----------------------------\n");
        System.out.printf("  Su  Mo  Tu  We  Th  Fr  Sa\n");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 7; j++) {
                System.out.printf("%4s", calendar[i][j]);
            }
            System.out.println();
        }

        scan.close(); // close scanner
    }

    /**
     * Get the weekday of a given date. This method follow the convention in the US
     * where the week begins with Sunday.
     * 
     * @param date
     * @return the weekday of date in integer (1 is Sunday, 7 is Saturday)
     */
    private static int getWeekDayOf(int month, int day, int year) {
        LocalDate date = LocalDate.of(year, month, day); // ISO
        int val = date.getDayOfWeek().getValue() + 1;
        return val == 8 ? val - 7 : val;
    }

    /**
     * Get the length of a given month in year.
     * 
     * @param month
     * @param year
     * @return the length of month in year
     */
    private static int getNumOfDays(int month, int year) {
        return LocalDate.of(year, month, 1).lengthOfMonth();
    }
}
