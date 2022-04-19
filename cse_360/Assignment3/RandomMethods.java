/*****
 * Name: Tyler Fichiera
 * CSE 360 Spring 2022
 * Assignment 3: JUnit Tests Template Code File
 *****/
public class RandomMethods {
  private static final char[] ALPHABET = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  private static final char[] VOWELS = {'a', 'e', 'i', 'o', 'u'};

  /*****
   * A variation of the function used in 
   * https://www.w3resource.com/java-exercises/conditional-statement/java-conditional-statement-exercise-7.php
   * Find the number of days in a month for a particular year.
   * @param month - the month number, e.g. 6 = June
   * @param year - the year number since a leap year will change the number of days in February
   * @return returnValue - a string indicating how many days are in a given month for a particular year
  *****/
  public static String daysInMonth( int month, int year ) {
    String returnValue = "";

    switch( month ) {
      case 1:
        returnValue = "January " + year + " has 31 days";
        break;
      case 2: 
        returnValue = "February " + year + " has ";
        /* If the year is a leap year, February has 29 days instead of 28 days */
        if( (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)) ) {
          returnValue += "29 days";
        } else {
          returnValue += "28 days";
        }
        break;
      case 3:
        returnValue = "March " + year + " has 31 days";
        break;
      case 4:
        returnValue = "April " + year + " has 30 days";
        break;
      case 5:
        returnValue = "May " + year + " has 31 days";
        break;
      case 6:
        returnValue = "June " + year + " has 30 days";
        break;
      case 7:
        returnValue = "July " + year + " has 31 days";
        break;
      case 8:
        returnValue = "August " + year + " has 31 days";
        break;
      case 9:
        returnValue = "September " + year + " has 30 days";
        break;
      case 10:
        returnValue = "October " + year + " has 31 days";
        break;
      case 11:
        returnValue = "November " + year + " has 30 days";
        break;
      case 12:
        returnValue = "December " + year + " has 31 days";
        break;
      default:
        returnValue = "Unknown month number";
        break;
    }
    
    return returnValue;
  }

  /*****
   * Given three numbers, find the smallest value.
   * @param number1 - One of the values to be compared
   * @param number2 - One of the values to be compared
   * @param number3 - One of the values to be compared
   * @return returnValue - the value of the smallest number
  *****/
  public static double smallestNumber( double number1, double number2, double number3 ) {
    double returnValue = 0.0;

    if (number1 < number2 && number1 < number3) {
      returnValue = number1;
    } else if (number2 < number1 && number2 < number3) {
      returnValue = number2;
    } else {
      returnValue = number3;
    }

    return returnValue;
  }

  /*****
   * Use a while loop to go through the given input string and count the number of 
   * consonants(all letters except a, e, i, o, u) in it
   * For example, "The quick brown fox jumps over the lazy dog."
   *      Function should return 11 (actually should be 24...)
   * @param input - input that is passed into the function
   * @return returnValue - the number of consonants in the input string
  *****/
  public static int numberOfConsonants(String input) {
    int returnValue = 0;

    for (char ch : input.toLowerCase().toCharArray()) {
      if (containsChar(ALPHABET, ch) && !containsChar(VOWELS, ch)) {
        returnValue++;
      }
    }

    return returnValue;
  }

  /*****
   * Check to see if the given string is a pangram (a sentence that has all the letters
   * in the alphabet).
   * @param input - a string of unknown length
   * @return returnValue - 'true' if input is a pangram. 'false' if input is not a pangram.
  *****/
  public static boolean isPangram(String input) {
    char[] alreadyChecked = new char[26];
    int checked = 0;

    for (char ch : input.toLowerCase().toCharArray()) {
      if (containsChar(ALPHABET, ch) && !containsChar(alreadyChecked, ch)) {
        alreadyChecked[checked] = ch;
        checked++;
      }
    }

    return checked == 26;
  }

  /*****
   * Private helper method to check if an array contains a certain char
   * @param arr - char array to check against
   * @param checkFor - char to check if it's in `arr`
   * @return returnValue - 'true' if input is a pangram. 'false' if input is not a pangram.
  *****/
  private static boolean containsChar(char[] arr, char checkFor) {
    for (char ch : arr)
      if (ch == checkFor) return true;
    return false;
  }
}