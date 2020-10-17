/*
CSE 110 83315 / T 1:30-2:20 PM
Assignment: Assignment 05
Author: Tyler Fichiera 1218959911
Description: Source for assignment 5
*/

public class Assignment05 {
    public static void main(String[] args) {
        // Tests for each method here
        // Compare console output to expected output

        // expected output: "Hello, and Welcome!"
        displayGreeting();

        // expected output: "Hello World"
        displayText("Hello World");
        
        // expected output: 6
        printTotal(1, 2, 3);
        
        // expected output: 6
        System.out.println(getTotal(1, 2, 3));
        
        // expected output: 2.0
        System.out.println(getAverage(1, 2, 3));
        
        // expected output: 2.0
        System.out.println(averageLength("A", "AB", "ABC"));
        
        // expected output: 1
        System.out.println(lengthOfShortest("A", "AB"));
        
        // expected output: "******"
        System.out.println(stringOfStars("ABCDEF"));
        
        // expected output: "******"
        System.out.println(maxStringOfStars("ABC", "ABCDEF"));
        
        // expected output: "******"
        System.out.println(midStringOfStars("ABC", "ABCDEF", "ABCDEFGHIJK"));
    }
    
    /** Displays "Hello, and welcome!" */
    static void displayGreeting() {
        System.out.println("Hello, and welcome!");
    }
    
    /**
     * Displays text from first parameter
     * @param text text to be displayed
    */
    static void displayText(String text) {
        System.out.println(text);
    }
    
    /**
     * Displays the sum of the three numbers
     * @param num1 first number
     * @param num2 second number
     * @param num3 third number
    */
    static void printTotal(int num1, int num2, int num3) {
        System.out.println(num1 + num2 + num3);
    }

    /**
     * Get the total of the three numbers provided
     * @param num1 first number
     * @param num2 second number
     * @param num3 third number
     * @return sum of the three numbers provided
    */
    static int getTotal(int num1, int num2, int num3) {
        return num1 + num2 + num3;
    }

    /**
     * Get the average of the three numbers provided
     * @param num1 first number
     * @param num2 second number
     * @param num3 third number
     * @return mean of the three numbers provided
    */
    static double getAverage(int num1, int num2, int num3) {
        // add three numbers then divide to find average
        return (num1 + num2 + num3) /  3.0;
    }

    /**
     * Get the average length of the three numbers provided
     * @param num1 first number
     * @param num2 second number
     * @param num3 third number
     * @return average length of the three numbers provided
    */
    static double averageLength(String str1, String str2, String str3) {
        // add lengths and then divide to find average
        return (str1.length() + str2.length() + str3.length()) /  3.0;
    }
    
    /**
     * Get the shortest length of the two strings
     * @param str1 first string
     * @param str2 second string
     * @return the shortest length of the two strings
    */
    static int lengthOfShortest(String str1, String str2) {
        // find the shortest length with if-statement
        int shortestLen;
        if (str1.length() <= str2.length()) {
            shortestLen = str1.length();
        } else {
            shortestLen = str2.length();
        }
        return shortestLen;
        // or like this but i'd prob get points taken off :/
        // return str1.length() <= str2.length() ? str1.length() : str2.length();
    }

    /**
     * Get a string of stars based on the length of a provided string
     * @param min string with length equal to the desired number of stars
     * @return string of stars based on the length of a provided string
    */
    static String stringOfStars(String str) {
        // pass length of string as number of stars
        return getStars(str.length());
    }

    /**
     * Get a string of stars based on the largest length of provided strings
     * @param str1 first string
     * @param str2 second string
     * @return string of stars based on the largest length of provided strings
    */
    static String maxStringOfStars(String str1, String str2) {
        // find the largest length with if-statement
        int maxLen;
        if (str1.length() >= str2.length()) {
            maxLen = str1.length();
        } else {
            maxLen = str2.length();
        }
        return getStars(maxLen);
    }

    /**
     * Get a string of stars based on the middle length of provided strings
     * @param str1 first string
     * @param str2 second string
     * @param str3 third string
     * @return string of stars based on the middle length of provided strings
    */
    static String midStringOfStars(String str1, String str2, String str3) {
        // find middle length string using if-else statement
        int midLen;
        if (
            // check str1
            str2.length() > str1.length() && str1.length() > str3.length() ||
            str3.length() > str1.length() && str1.length() > str2.length()
        ) {
            midLen = str1.length();
		} else if (
            // check str2
            str1.length() > str2.length() && str2.length() > str3.length() ||
            str3.length() > str2.length() && str2.length() > str1.length()
        ) {
            midLen = str2.length();
		} else {
            // must be str3 if not str1 or str2
            midLen = str3.length();
		}
        return getStars(midLen);
    }

    // private method to reduse code duplication
    /**
     * Get a string of stars with given len
     * @param len number of stars in string
     * @return string of stars with given len
    */
    private static String getStars(int len) {
        // init String and then concat '*'s
        String stars = new String("");
        for (int i = 0; i < len; i++) stars += '*';
        return stars;
    }
}
