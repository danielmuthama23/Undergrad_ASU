/*
CSE 110 83315 / T 1:30-2:20 PM
Assignment: Assignment 06
Author: Tyler Fichiera 1218959911
Description: Source for assignment 6
*/

public class Assignment06 {
    public static void main(String[] args) {
        // Write any code here that you may wish to test your methods defined below.
        // Compare console output to expected output

        // create array to use in all the tests
        int[] myArray = {1, 22, 333, 400, 5005, 9};

        // expected output: "1, 22, 333, 400, 5005, 9"
        printArray(myArray, ", ");
        System.out.println();

        // expected output: 1
        System.out.println(getFirst(myArray));

        // expected output: 9
        System.out.println(getLast(myArray));

        // expected output: "22, 333, 400, 5005, 9"
        printArray(getAllButFirst(myArray), ", ");
        System.out.println();

        // expected output: 0
        System.out.println(getIndexOfMin(myArray));

        // expected output: 4
        System.out.println(getIndexOfMax(myArray));

        // expected output: "1, 5005, 333, 400, 22, 9"
        printArray(swapByIndex(myArray, 1, 4), ", ");
        System.out.println();

        // expected output: "1, 5005, 333, 22, 9"
        printArray(removeAtIndex(myArray, 3), ", ");
        System.out.println();

        // expected output: "1, 5005, 777, 333, 400, 22, 9"
        printArray(insertAtIndex(myArray, 2, 777), ", ");
        System.out.println();

        // expected output: false
        System.out.println(isSorted(myArray));
    }

    /**
     * Prints out all elements in arr separated by str
     * @param arr array of ints
     * @param str the element separator
    */
    public static void printArray(int[] arr, String str) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
            // dont print out separator after last elements
            if (i < arr.length - 1) System.out.print(str);
        }
    }

    /**
     * Get the first element of an int array
     * @param arr array of ints
     * @return first element of arr
    */
    public static int getFirst(int[] arr) {
        return arr[0]; // element at index 0
    }

    /**
     * Get the last element of an int array
     * @param arr array of ints
     * @return last element of arr
    */
    public static int getLast(int[] arr) {
        return arr[arr.length - 1]; // last element in the array
    }

    /**
     * Get a new array with all of the values in the argument arr except the first value
     * @param arr array of ints
     * @return array with all of the values in the argument arr except the first value
    */
    public static int[] getAllButFirst(int[] arr) {
        // new array with length one less than arr.length
        int[] newArr = new int[arr.length - 1];
        // loop through all elements besides the first
        for (int i = 1; i < arr.length; i++) {
            // add elements to new array
            newArr[i - 1] = arr[i];
        }
        return newArr;
    }

    /**
     * Get the index of the least value in arr
     * @param arr array of ints
     * @return index of the least value in arr
    */
    public static int getIndexOfMin(int[] arr) {
        int minIndex = 0;
        // loop through all elements besides the first
        for (int i = 1; i < arr.length; i++) {
            // compare current element to the current lowest index
            // if it is smaller, change minIndex
            if (arr[i] < arr[minIndex]) {
                minIndex = i;
            }
        }
        return minIndex;
    }
    
    
    /**
     * Get the index of the largest value in arr
     * @param arr array of ints
     * @return index of the largest value in arr
    */
    public static int getIndexOfMax(int[] arr) {
        int maxIndex = 0;
        // loop through all elements besides the first
        for (int i = 1; i < arr.length; i++) {
            // compare current element to the current largest index
            // if it is larger, change maxIndex
            if (arr[i] > arr[maxIndex]) {
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    /**
     * Swap the values of an array at two given indexes
     * @param arr array of ints
     * @param index1 index one
     * @param index2 index two
     * @return a reference to arr with the indexes swapped
    */
    public static int[] swapByIndex(int[] arr, int index1, int index2) {
        // store original values
        int val1 = arr[index1];
        int val2 = arr[index2];
        // swap the values in the original array
        arr[index1] = val2;
        arr[index2] = val1;
        // return reference to original array
        return arr;
    }

    /**
     * Get a new array with all the values in arr except the value at index
     * @param arr array of ints
     * @param index index to remove
     * @return new array with all the values in arr except the value at index
    */
    public static int[] removeAtIndex(int[] arr, int index) {
        // new array with length one less than arr.length
        int[] newArr = new int[arr.length - 1];
        int c = 0; // use counter to hold current index of newArr
        for (int i = 0; i < arr.length; i++) {
            // if index doesnt equal second arg, add to newArr
            // and update newArr counter var (c)
            if (i != index) {
                newArr[c] = arr[i];
                c++;
            }
        }
        return newArr;
    }

    /**
     * Get a new array with all of the values 
     * in the argument arr and including the third argument value 
     * inserted at the index specified by the second argument value.
     * @param arr array of ints
     * @param index index to insert at
     * @param value value to insert at index
     * @return new array with value inserted at index
    */
    public static int[] insertAtIndex(int[] arr, int index, int value) {
        // new array with length one more than arr.length
        int[] newArr = new int[arr.length + 1];
        int c = 0; // use counter to hold current index of arr
        for (int i = 0; i < arr.length + 1; i++) {
            // check if current index of loop is equal to second arg
            // if it is, insert val
            if (i == index) {
                newArr[i] = value;
            } else {
                newArr[i] = arr[c];
                c++; // keep track of current index of arr
            }
        }
        return newArr;
    }

    /**
     * Check if arr is sorted in ascending order
     * @param arr array of ints
     * @return true/false if arr is ascending
    */
    public static boolean isSorted(int[] arr) {
        // loop through all elements besides the first
        for (int i = 1; i < arr.length; i++) {
            // compare current element to the one before
            if (arr[i - 1] > arr[i]) return false;
            // return false if element before is greater
            // than the one following it
        }
        return true;
    }

}
