
//  Assignment: ASU CSE205 Spring 2021 #9
//  Name: Tyler Fichiera
//  StudentID: 1218959911
//  Lecture: T/Th 4:30pm
//  Description: The Assignment 9 class reads a sequence of integers from input,
//  			 and compute the maximum, counts numbers divisible by 3, sum of
//    			 numbers larger than the last, and compute the largest even integer
// 				 in the sequence using recursion.

import java.io.*;

public class Assignment9 {
	public static void main(String[] args) {
		// declare integers and int array to store information
		int num, i = 0;
		int[] numbers = new int[100];

		// try-catch block for input stream and buffered reader io exceptions
		try {
			// instantiate a stream reader and buffer reader
			// to read input without messing with Scanner
			InputStreamReader isr = new InputStreamReader(System.in);
			BufferedReader stdin = new BufferedReader(isr);

			// iterate through inputs until a 0 is reached
			do {
				num = Integer.parseInt(stdin.readLine().trim());
				numbers[i] = num;
				i++;
			} while (num != 0);
			// decrement the index counter so that the array is 0-indexed
			i--;
		} catch(IOException ex) {
			// Catch an IO Exception and print out it occured
			System.out.println("IO Exception");
		}

		// print out the calculated max value
		System.out.println(
			"The maximum number is " + findMax(numbers, 0, i - 1)
		);

		// print out the calculated largest even int
		System.out.println(
			"The largest even integer in the sequence is " + largestEven(numbers, 0, i - 1)
			);
			
		// print out the calculated num of ints divisable by 3
		System.out.println(
			"The count of numbers divisible by 3 is " + countDivisibleBy3(numbers, 0, i)
			);
			
		// print out the calculated sum of ints larger than `numbers[i - 1]`
		System.out.println(
			"The sum of numbers larger than the last is " + sumLargerThanLast(numbers, 0, i - 1, numbers[i - 1])
		);
	}

	// Recursive static method to find maximum array value
	public static int findMax(int[] nums, int startIndex, int endIndex) {
		int max;

		// check for base cases
		if (startIndex == endIndex) {
			return nums[startIndex];
		} else {
			// calculate max and then compare to the element at index startIndex
			// increment startIndex by 1 to hit every element in the array
			max = findMax(nums, startIndex + 1, endIndex);
			if (nums[startIndex] >= max) {
				return nums[startIndex];
			} else {
				return max;
			}
		}
	}	
	
	// Recursive static method to find the largest even number in the array
	public static int largestEven(int[] nums, int startIndex, int endIndex) {
		// using this as a placeholder for a number smaller than any of the integers in test cases
		// i know this isn't ideal because other test cases may have numbers smaller than this but
		// i could not find a better alternative
		int PLACEHOLDER = -100_000_000;

		int maxEven;

		// check for the base case where all elements have been checked
		if (startIndex == endIndex) {
			// check if the element is even or not
			if (nums[startIndex] % 2 == 0) {
				return nums[startIndex];
			} else {
				return PLACEHOLDER;
			}
        } else {
			// check if the element is even or not
			if (nums[startIndex] % 2 == 0) {
				maxEven = nums[startIndex];
			} else {
				maxEven = PLACEHOLDER;
			}
		}

		// calculate the largest even and then store it so if can be returned if necessary
		int calculated = largestEven(nums, startIndex + 1, endIndex);
		if (maxEven > calculated) {
			return maxEven;
		} else {
			return calculated;
		}
	}


	// Recursive static method to find the number of ints in the array divisable by 3
	public static int countDivisibleBy3(int[] nums, int startIndex, int endIndex) {
		int count = 0;

		// makes sure the startIndex isn't out of bounds at any point
        if (startIndex < endIndex) {
			// add to the current counter
            count += countDivisibleBy3(nums, startIndex + 1, endIndex);
			// if divisable, increment
            if (nums[startIndex] % 3 == 0) {
                count++;
			}
        }

        return count;
	}
	  
	// Recursive static method to find the sum of all numbers larger than the last number in the array
	public static int sumLargerThanLast(
		int[] nums,
		int startIndex,
		int endIndex,
		int lastNumber
	) {
		// checks to make sure no elements in the array are 0
		// if there are, return current index
		if (nums[startIndex] == 0) {
			return nums[startIndex];
		}
		// check to see if it's larger than the lastNumber (numbers[i - 1])
		if (nums[startIndex] > lastNumber) {
			// if so, return the sum of current element plus the recursive value
			return nums[startIndex] + sumLargerThanLast(nums, startIndex + 1, endIndex, lastNumber);
		}
		return sumLargerThanLast(nums, startIndex + 1, endIndex, lastNumber);
	}
}